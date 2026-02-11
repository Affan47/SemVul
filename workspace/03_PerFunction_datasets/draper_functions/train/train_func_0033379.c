init_global(VOID)
{
    BOOL ok = TRUE;

    return_code = RC_OK;


    inpfilename = init_estr(32);
    msgbuf = init_estr(64);

    ok = (inpfilename && msgbuf);

    return (ok);
}
