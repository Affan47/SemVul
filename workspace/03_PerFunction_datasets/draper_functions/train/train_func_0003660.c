plfit_estimate_alpha_continuous_sorted(double* xs, size_t n, double xmin,
        const plfit_continuous_options_t* options, plfit_result_t *result) {
    double *begin, *end;

    if (!options)
        options = &plfit_continuous_default_options;

    begin = xs;
    end = xs + n;
    while (begin < end && *begin < xmin)
        begin++;

    PLFIT_CHECK(plfit_i_estimate_alpha_continuous_sorted(begin, end-begin,
                xmin, &result->alpha));
    PLFIT_CHECK(plfit_i_ks_test_continuous(begin, end, result->alpha,
                xmin, &result->D));

    if (options->finite_size_correction)
        plfit_i_perform_finite_size_correction(result, end-begin);
    result->xmin = xmin;

    PLFIT_CHECK(plfit_log_likelihood_continuous(begin, end-begin, result->alpha,
                result->xmin, &result->L));
    PLFIT_CHECK(plfit_i_calculate_p_value_continuous(xs, n, options, 1, result));

    return PLFIT_SUCCESS;
}
