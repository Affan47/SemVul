df_gls_ct_cval (int T)
{

    static double df_gls_ct_cvals[4][4] = {

	{ -2.89, -3.19, -3.46, -3.77 },
	{ -2.74, -3.03, -3.29, -3.58 },
	{ -2.64, -2.93, -3.18, -3.46 },
	{ -2.57, -2.89, -3.15, -3.48 }
    };
    int i = 3;

    if (T <= 50){
	i = 0;
    } else if (T <= 100){
	i = 1;
    } else if (T <= 200){
	i = 2;
    }

    return df_gls_ct_cvals[i];
}
