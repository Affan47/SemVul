is_reject_binomial_p(const double alpha,
                     const double p,
                     const unsigned n_success,
                     const unsigned n_failure) {

    static const unsigned exact_test_threshold(250);

    const unsigned n_trial(n_success+n_failure);

    if (n_trial > exact_test_threshold) {
        return is_reject_binomial_p_chi_sqr(alpha,p,n_success,n_failure);
    } else {
        return is_reject_binomial_p_exact(alpha,p,n_success,n_failure);
    }
}
