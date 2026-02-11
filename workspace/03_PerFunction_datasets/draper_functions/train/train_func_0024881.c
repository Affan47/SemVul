calc_sample_specific_model_conf(int n_windows,
                                     char sex,
                                     unsigned char *window_chr,
                                     double *cov,
                                     unsigned char *filtered_flag,
                                     unsigned char *hom_del_flag,
                                     double *lambda,
                                     double *sigma_dip,
                                     double *model_conf) {
    int i;
    for (i = 0; i < n_windows; i++) {
        if (filtered_flag[i]) continue;
        double cov_conf = cov_confidence_term(expected_copy_number(sex, window_chr[i]),
                                              cov[i], hom_del_flag[i], lambda[i], sigma_dip[i]);
        model_conf[i] = fmin(model_conf[i], cov_conf);
    }
}
