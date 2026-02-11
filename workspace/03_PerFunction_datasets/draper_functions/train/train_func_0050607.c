call(const unsigned pos,
     snp_pos_info& norm_pi,
     snp_pos_info& tumor_pi) {

    static dependent_prob_cache dpcache;

    const char ref_base(norm_pi.ref_base);


    extra_position_data norm_epd;
    extra_position_data tumor_epd;

    static const bool is_dep(false);
    const bool is_include_tier2(false);
    extended_pos_data normald(&norm_pi,norm_epd,
                              ref_base,_opt,dpcache,is_dep,is_include_tier2);
    extended_pos_data tumord(&tumor_pi,tumor_epd,
                             ref_base,_opt,dpcache,is_dep,is_include_tier2);


    somatic_snv_genotype_grid sgtg;
    _dopt_ptr->sscaller_strand_grid().position_somatic_snv_call(normald.good_epi,
                                                                tumord.good_epi,
                                                                NULL,
                                                                NULL,
                                                                sgtg);

    if (! sgtg.is_output()) return;

    static const char chrom_name[] = "sim";
    _os << chrom_name << '\t'
        << pos << '\t'
        << ".";

    write_vcf_somatic_snv_genotype_strand_grid(_opt,sgtg,
                                               normald,
                                               tumord,
                                               normald,
                                               tumord,
                                               _os);

    _os << "\n";
}
