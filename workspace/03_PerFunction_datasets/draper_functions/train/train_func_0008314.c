xsh_detmon_pernoise_rm_bg(cpl_image * image, int nsamples, int nffts)
{
    cpl_vector             *values = cpl_vector_new(nsamples * nffts);

    int                     rejected;
    int i, j;
    cpl_vector *xy_pos = cpl_vector_new(nsamples * nffts * 2);
    double mse = 0;
    cpl_polynomial * poly_2d = 0;
    cpl_image * poly_ima = 0;
    cpl_size degree = 3;
    cpl_error_code error = CPL_ERROR_NONE;
    cpl_matrix * samppos = 0;
    cpl_vector * fitresidual = 0;

    for(i = 1; i <= nffts; i++) {
        for(j = 1; j <= nsamples; j++) {
            cpl_vector_set(xy_pos, (i - 1) * nsamples + (j - 1), j);
            cpl_vector_set(xy_pos, (i - 1) * nsamples + (j - 1) + nsamples * nffts, i);
            cpl_vector_set(values, (i - 1) * nsamples + (j - 1),
                           cpl_image_get(image, j, i, &rejected));
            error = cpl_error_get_code();
            if (error != CPL_ERROR_NONE)
            {
            	break;
            }
        }
        if (error != CPL_ERROR_NONE)
        {
        	break;
        }
    }
    if (error != CPL_ERROR_NONE)
    {
    	goto cleanup;
    }
#if defined CPL_VERSION_CODE && CPL_VERSION_CODE >= CPL_VERSION(4, 8, 0)
    poly_2d = cpl_polynomial_new(2);
    samppos =
	cpl_matrix_wrap(2, nsamples * nffts, cpl_vector_get_data(xy_pos));
    fitresidual = cpl_vector_new(nsamples * nffts);
    cpl_polynomial_fit(poly_2d, samppos, NULL, values, NULL,
		       CPL_FALSE, NULL, &degree);

    cpl_vector_fill_polynomial_fit_residual(fitresidual, values, NULL, poly_2d,
					    samppos, NULL);
    cpl_matrix_unwrap(samppos);
    mse = cpl_vector_product(fitresidual, fitresidual)
	/ cpl_vector_get_size(fitresidual);
    cpl_vector_delete(fitresidual);

#else
    poly_2d = cpl_polynomial_fit_2d_create(xy_pos, values, 3, &mse);
#endif

    poly_ima = cpl_image_new(nsamples, nffts, CPL_TYPE_FLOAT);

    cpl_image_fill_polynomial(poly_ima, poly_2d, 1, 1, 1, 1);

    cpl_image_subtract(image, poly_ima);

cleanup:
    cpl_polynomial_delete(poly_2d);
    cpl_image_delete(poly_ima);
    cpl_vector_delete(xy_pos);
    cpl_vector_delete(values);

    return cpl_error_get_code();
}
