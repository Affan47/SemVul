itrscg_(integer *n, integer *nb, integer *ia, integer *ja, doublereal *a, doublereal *ub,
            doublereal *ub1, doublereal *db, doublereal *db1, doublereal *wb, doublereal *tri)
{
    static doublereal c1, c2, c3, c4;
    static logical q1;
    static integer nr;
    static doublereal con;
    static doublereal dnrm;
    static doublereal gamold;
    static doublereal rhoold;


    nr = *n - *nb;
    if (itcom2_1.adapt)
        chgcon_(tri, &gamold, &rhoold, &c__2);


    itcom3_1.delnnm = itpackddot_(nb, db, &c__1, db, &c__1);
    dnrm = itcom3_1.delnnm;
    con = itcom3_1.cme;
    pstop_(nb, &ub[nr], &dnrm, &con, &c__2, &q1);
    if (itcom2_1.halt)
        goto L30;


    vfill_(&nr, ub1, &c_b21);
    prsred_(nb, &nr, ia, ja, a, db, ub1);
    vfill_(nb, wb, &c_b21);
    prsblk_(nb, &nr, ia, ja, a, ub1, wb);
    dnrm = itpackddot_(nb, db, &c__1, wb, &c__1);
    if (itcom1_1.isym != 0)
        rhoold = itpackddot_(nb, wb, &c__1, db1, &c__1);

    parcon_(&dnrm, &c1, &c2, &c3, &c4, &gamold, &rhoold, &c__2);


    sum3_(nb, &c1, db, &c2, &ub[nr], &c3, &ub1[nr]);
    sum3_(nb, &c1, wb, &c4, db, &c3, db1);


L30:
    iterm_(nb, &a[nr], &ub[nr], wb, &c__6);

    return 0;
}
