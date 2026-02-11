selaAddHitMiss(SELA  *sela)
{
SEL  *sel;

    PROCNAME("selaAddHitMiss");

    if (!sela) {
        if ((sela = selaCreate(0)) == NULL)
            return (SELA *)ERROR_PTR("sela not made", procName, NULL);
    }

#if 0
    sel = selCreateBrick(3, 3, 1, 1, 2);
    selaAddSel(sela, sel, "sel_bad", 0);
#endif


    sel = selCreateBrick(3, 3, 1, 1, 2);
    selSetElement(sel, 1, 1, 1);
    selaAddSel(sela, sel, "sel_3hm", 0);


    sel = selCreateBrick(2, 3, 0, 1, 1);
    selSetElement(sel, 1, 0, 2);
    selSetElement(sel, 1, 1, 2);
    selSetElement(sel, 1, 2, 2);
    selaAddSel(sela, sel, "sel_3de", 0);

    sel = selCreateBrick(2, 3, 1, 1, 1);
    selSetElement(sel, 0, 0, 2);
    selSetElement(sel, 0, 1, 2);
    selSetElement(sel, 0, 2, 2);
    selaAddSel(sela, sel, "sel_3ue", 0);

    sel = selCreateBrick(3, 2, 1, 0, 1);
    selSetElement(sel, 0, 1, 2);
    selSetElement(sel, 1, 1, 2);
    selSetElement(sel, 2, 1, 2);
    selaAddSel(sela, sel, "sel_3re", 0);

    sel = selCreateBrick(3, 2, 1, 1, 1);
    selSetElement(sel, 0, 0, 2);
    selSetElement(sel, 1, 0, 2);
    selSetElement(sel, 2, 0, 2);
    selaAddSel(sela, sel, "sel_3le", 0);


    sel = selCreateBrick(13, 6, 6, 2, 0);
    selSetElement(sel, 0, 3, 2);
    selSetElement(sel, 0, 5, 1);
    selSetElement(sel, 4, 2, 2);
    selSetElement(sel, 4, 4, 1);
    selSetElement(sel, 8, 1, 2);
    selSetElement(sel, 8, 3, 1);
    selSetElement(sel, 12, 0, 2);
    selSetElement(sel, 12, 2, 1);
    selaAddSel(sela, sel, "sel_sl1", 0);

    return sela;
}
