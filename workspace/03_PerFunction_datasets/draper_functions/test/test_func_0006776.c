uaegfx_card_install (TrapContext *ctx, uae_u32 extrasize)
{
    uae_u32 functable, datatable, a2;
    uaecptr openfunc, closefunc, expungefunc;
    uaecptr findcardfunc, initcardfunc;
    uaecptr exec = get_long (4);

    if (uaegfx_old || !gfxmem_start)
        return NULL;

    uaegfx_resid = ds (_T("UAE Graphics Card 3.3"));
    uaegfx_vblankname = ds (_T("UAE Graphics Card VBLANK"));
    uaegfx_portsname = ds (_T("UAE Graphics Card PORTS"));


    openfunc = here ();
    calltrap (deftrap (gfx_open)); dw (RTS);


    closefunc = here ();
    calltrap (deftrap (gfx_close)); dw (RTS);


    expungefunc = here ();
    calltrap (deftrap (gfx_expunge)); dw (RTS);


    findcardfunc = here ();
    calltrap (deftrap (picasso_FindCard)); dw (RTS);


    initcardfunc = here ();
    calltrap (deftrap (picasso_InitCard)); dw (RTS);

    functable = here ();
    dl (openfunc);
    dl (closefunc);
    dl (expungefunc);
    dl (EXPANSION_nullfunc);
    dl (findcardfunc);
    dl (initcardfunc);
    dl (0xFFFFFFFF);

    datatable = makedatatable (uaegfx_resid, uaegfx_resname, 0x09, -50, UAEGFX_VERSION, UAEGFX_REVISION);

    a2 = m68k_areg (regs, 2);
    m68k_areg (regs, 0) = functable;
    m68k_areg (regs, 1) = datatable;
    m68k_areg (regs, 2) = 0;
    m68k_dreg (regs, 0) = CARD_SIZEOF + extrasize;
    m68k_dreg (regs, 1) = 0;
    uaegfx_base = CallLib (ctx, exec, -0x54);
    m68k_areg (regs, 2) = a2;
    if (!uaegfx_base)
        return 0;
    m68k_areg (regs, 1) = uaegfx_base;
    CallLib (ctx, exec, -0x18c);
    m68k_areg (regs, 1) = EXPANSION_explibname;
    m68k_dreg (regs, 0) = 0;
    put_long (uaegfx_base + CARD_EXPANSIONBASE, CallLib (ctx, exec, -0x228));
    put_long (uaegfx_base + CARD_EXECBASE, exec);
    put_long (uaegfx_base + CARD_NAME, uaegfx_resname);
    put_long (uaegfx_base + CARD_RESLIST, uaegfx_base + CARD_SIZEOF);
    put_long (uaegfx_base + CARD_RESLISTSIZE, extrasize);


    if (currprefs.win32_rtgvblankrate >= -1)
        initvblankirq (ctx, uaegfx_base);

    write_log (_T("uaegfx.card %d.%d init @%08X\n"), UAEGFX_VERSION, UAEGFX_REVISION, uaegfx_base);
    uaegfx_active = 1;
    return uaegfx_base;
}
