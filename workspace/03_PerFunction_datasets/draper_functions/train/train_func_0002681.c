dcbias_(integer *len, real *speech, real *sigout)
{

    integer i__1;


    real bias;
    integer i__;


    --sigout;
    --speech;


    bias = 0.f;
    i__1 = *len;
    for (i__ = 1; i__ <= i__1; ++i__) {
	bias += speech[i__];
    }
    bias /= *len;
    i__1 = *len;
    for (i__ = 1; i__ <= i__1; ++i__) {
	sigout[i__] = speech[i__] - bias;
    }
    return 0;
}
