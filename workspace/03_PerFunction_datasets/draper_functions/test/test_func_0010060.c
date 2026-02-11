calc_cn_emission_logp(int n_windows,
                           char sex,
                           unsigned char *window_chr,
                           double *cov,
                           unsigned char *filtered_flag,
                           unsigned char *hom_del_flag,
                           double *lambda,
                           double *sigma_dip,
                           double **cn_emission_logp) {
    int i, j;
    for (i = 0; i < n_windows; i++) {
        if (filtered_flag[i]) continue;
        int norm_cn = expected_copy_number(sex, window_chr[i]);
        int max_cn = ONE_MORE_THAN_MAX_CN;
        if (norm_cn == HAPLOID) max_cn = 2;


        cn_emission_logp[i][0] = homozygous_del_log_likelihood(cov[i], hom_del_flag[i], lambda[i]);
        for (j = 1; j <= max_cn; j++) {
            cn_emission_logp[i][j] = gaussian_log_likelihood(cov[i], j, sigma_dip[i]);
        }


        double evidence = 0.0;
        for (j = 0; j <= max_cn; j++)
            evidence += exp(cn_emission_logp[i][j]);
        evidence = log(evidence);
        for (j = 0; j <= max_cn; j++)
            cn_emission_logp[i][j] -= evidence;
    }
}
