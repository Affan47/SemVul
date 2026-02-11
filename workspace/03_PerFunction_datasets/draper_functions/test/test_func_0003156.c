create_gaussian_blur_kernel (gint    radius,
                             gdouble sigma,
                             gint*   length)
{
	const gdouble   scale2 = 2.0f * sigma * sigma;
	const gdouble   scale1 = 1.0f / (G_PI * scale2);
	const gint      size = 2 * radius + 1;
	const gint      n_params = size * size;
	pixman_fixed_t* params;
	gdouble*        tmp;
	gdouble         sum;
	gint            x;
	gint            y;
	gint            i;

        tmp = g_newa (double, n_params);


        for (i = 0, sum = 0, x = -radius; x <= radius; ++x) {
                for (y = -radius; y <= radius; ++y, ++i) {
                        const gdouble u = x * x;
                        const gdouble v = y * y;

                        tmp[i] = scale1 * exp (-(u+v)/scale2);

                        sum += tmp[i];
                }
        }


        params = g_new (pixman_fixed_t, n_params + 2);

        params[0] = pixman_int_to_fixed (size);
        params[1] = pixman_int_to_fixed (size);

        for (i = 0; i < n_params; ++i)
                params[2 + i] = pixman_double_to_fixed (tmp[i] / sum);

        if (length)
                *length = n_params + 2;

        return params;
}
