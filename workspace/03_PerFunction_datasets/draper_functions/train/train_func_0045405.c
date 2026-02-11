omgchg_(integer *ndummy)
{

    doublereal d__1;


    static doublereal del1, del2;
    (void)ndummy;


    if (itcom1_1.in - itcom1_1.is < 3)
        return FALSE_;

    if (itcom3_1.specr == 0.)
        goto L10;

    if (itcom3_1.specr >= itcom3_1.spr)
        return FALSE_;

    d__1 = 1. - itcom3_1.specr / itcom3_1.spr;
    del1 = -log(abs((1. - sqrt(abs(1.-itcom3_1.specr))) /
                    (1. + sqrt(abs(1.-itcom3_1.specr))) /
                    ((1. - sqrt(abs(d__1))) /
                     (1. + sqrt(abs(d__1))))));
    del2 = -log(abs((1. - sqrt(abs(1. - itcom3_1.spr))) / (1. + sqrt(abs(1. - itcom3_1.spr)))));
    if (del1 / del2 >= itcom3_1.ff)
        return FALSE_;

L10:
    return TRUE_;
}
