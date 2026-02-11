get_prior(const blt_float_t* normal_lnprior,
          const unsigned ref_gt,
          const blt_float_t sse_rate,
          const blt_float_t sseb_fraction,
          const blt_float_t somatic_normal_noise_rate,
          const bool is_somatic_normal_noise_rate,
          std::vector<blt_float_t>& grid_normal_lnprior,
          std::vector<blt_float_t>& somatic_marginal_lnprior) {

    get_nostrand_marginal_prior(normal_lnprior,ref_gt,sse_rate,sseb_fraction,grid_normal_lnprior);
    if (is_somatic_normal_noise_rate) {
        get_nostrand_marginal_prior(normal_lnprior,ref_gt,somatic_normal_noise_rate,0,somatic_marginal_lnprior);
    } else {
        get_nostrand_marginal_prior(normal_lnprior,ref_gt,sse_rate,sseb_fraction,somatic_marginal_lnprior);
    }

    const blt_float_t strand_sse_rate(sse_rate*sseb_fraction);


    const blt_float_t ln_strand_sse_rate( std::log(strand_sse_rate) );


    static const blt_float_t error_mod( -std::log(static_cast<blt_float_t>(DIGT_SGRID::HET_RES*2)) );


    static const unsigned n_strand_het_axes(3);
    blt_float_t strand_axis_prior[n_strand_het_axes];

    double throwaway_sum(0);
    for (unsigned sgt(0); sgt<n_strand_het_axes; ++sgt) {
        strand_axis_prior[sgt] = normal_lnprior[ref_gt]+ln_one_third;
        throwaway_sum += std::exp(strand_axis_prior[sgt]);
    }

    throwaway_sum /= 2.;
    throwaway_sum = 1. - throwaway_sum;


    for (unsigned ngt(DIGT_SGRID::PRESTRAND_SIZE); ngt<(DIGT_SGRID::SIZE); ++ngt) {
        const unsigned sgt(DIGT_SGRID::get_strand_state(ngt));
        grid_normal_lnprior[ngt] = (strand_axis_prior[sgt]+ln_strand_sse_rate+error_mod);
    }

#ifdef SOMATIC_DEBUG
    throwaway_sum *= std::exp(ln_strand_sse_rate);

    check_ln_distro(grid_normal_lnprior.begin(),
                    grid_normal_lnprior.end(),
                    "somatic prior",
                    0.0001,
                    1.-throwaway_sum);
#endif
}
