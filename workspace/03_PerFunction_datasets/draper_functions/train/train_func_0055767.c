norm_s3_func_x(FLOAT hf_slope)
{
    double  lim_a = 0, lim_b = 0;
    {
        double  x = 0, l, h;
        for (x = 0; s3_func_x(x, hf_slope) > 1e-20; x -= 1);
        l = x;
        h = 0;
        while (fabs(h - l) > 1e-12) {
            x = (h + l) / 2;
            if (s3_func_x(x, hf_slope) > 0) {
                h = x;
            }
            else {
                l = x;
            }
        }
        lim_a = l;
    }
    {
        double  x = 0, l, h;
        for (x = 0; s3_func_x(x, hf_slope) > 1e-20; x += 1);
        l = 0;
        h = x;
        while (fabs(h - l) > 1e-12) {
            x = (h + l) / 2;
            if (s3_func_x(x, hf_slope) > 0) {
                l = x;
            }
            else {
                h = x;
            }
        }
        lim_b = h;
    }
    {
        double  sum = 0;
        int const m = 1000;
        int     i;
        for (i = 0; i <= m; ++i) {
            double  x = lim_a + i * (lim_b - lim_a) / m;
            double  y = s3_func_x(x, hf_slope);
            sum += y;
        }
        {
            double  norm = (m + 1) / (sum * (lim_b - lim_a));

            return norm;
        }
    }
}
