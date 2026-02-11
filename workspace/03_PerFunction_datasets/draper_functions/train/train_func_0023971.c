itjsi_(integer *n, integer *ia, integer *ja, doublereal *a, doublereal *rhs,
           doublereal *u, doublereal *u1, doublereal *d, integer *icnt)
{
    static doublereal c1, c2, c3;
    static logical q1;
    static doublereal con;
    static doublereal dnrm;
    static doublereal dtnrm;
    static doublereal oldnrm;


    if (itcom1_1.in == 0)
        *icnt = 0;


    itpackdcopy_(n, rhs, &c__1, d, &c__1);
    pjac_(n, ia, ja, a, u, d);
    vevmw_(n, d, u);


    oldnrm = itcom3_1.delnnm;
    itcom3_1.delnnm = itpackddot_(n, d, &c__1, d, &c__1);
    dnrm = itcom3_1.delnnm;
    con = itcom3_1.cme;
    pstop_(n, u, &dnrm, &con, &c__1, &q1);
    if (itcom2_1.halt)
        goto L40;

    if (! itcom2_1.adapt)
        goto L30;

    if (! tstchg_(&c__1))
        goto L10;


    dtnrm = pvtbv_(n, ia, ja, a, d);
    chgsi_(&dtnrm, &c__1);
    if (! itcom2_1.adapt)
        goto L30;

    goto L20;


L10:
    if (itcom2_1.caseii)
        goto L30;

    if (! chgsme_(&oldnrm, icnt))
        goto L30;

    *icnt = 0;


L20:
    itpackdcopy_(n, u, &c__1, u1, &c__1);
    itpackdaxpy_(n, &itcom3_1.gamma, d, &c__1, u1, &c__1);
    goto L40;


L30:
    parsi_(&c1, &c2, &c3, &c__1);
    sum3_(n, &c1, d, &c2, u, &c3, u1);


L40:
    iterm_(n, a, u, d, &c__2);

    return 0;
}
