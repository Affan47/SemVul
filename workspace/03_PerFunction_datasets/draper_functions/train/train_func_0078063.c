lgammacor(gnm_float x)
{
    static const gnm_float algmcs[15] = {
	GNM_const(+.1666389480451863247205729650822e+0),
	GNM_const(-.1384948176067563840732986059135e-4),
	GNM_const(+.9810825646924729426157171547487e-8),
	GNM_const(-.1809129475572494194263306266719e-10),
	GNM_const(+.6221098041892605227126015543416e-13),
	GNM_const(-.3399615005417721944303330599666e-15),
	GNM_const(+.2683181998482698748957538846666e-17),
	GNM_const(-.2868042435334643284144622399999e-19),
	GNM_const(+.3962837061046434803679306666666e-21),
	GNM_const(-.6831888753985766870111999999999e-23),
	GNM_const(+.1429227355942498147573333333333e-24),
	GNM_const(-.3547598158101070547199999999999e-26),
	GNM_const(+.1025680058010470912000000000000e-27),
	GNM_const(-.3401102254316748799999999999999e-29),
	GNM_const(+.1276642195630062933333333333333e-30)
    };

    gnm_float tmp;

#ifdef NOMORE_FOR_THREADS
    static int nalgm = 0;
    static gnm_float xbig = 0, xmax = 0;


    if (nalgm == 0) {

	nalgm = chebyshev_init(algmcs, 15, GNM_EPSILON/2);
	xbig = 1 / gnm_sqrt(GNM_EPSILON/2);
	xmax = gnm_exp(fmin2(gnm_log(GNM_MAX / 12), -gnm_log(12 * GNM_MIN)));

    }
#else


# define nalgm 5
# define xbig  GNM_const(94906265.62425156)
# define xmax  GNM_const(3.745194030963158e306)
#endif

    if (x < 10)
	ML_ERR_return_NAN
    else if (x >= xmax) {
	ML_ERROR(ME_UNDERFLOW);
	return ML_UNDERFLOW;
    }
    else if (x < xbig) {
	tmp = 10 / x;
	return chebyshev_eval(tmp * tmp * 2 - 1, algmcs, nalgm) / x;
    }
    else return 1 / (x * 12);
}
