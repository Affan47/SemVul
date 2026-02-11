write_diploid_genotype_allele(const blt_options& opt,
                              const snp_pos_info& pi,
                              const diploid_genotype& dgt,
                              std::ostream& os,
                              const unsigned hpol) {

    const result_set& ge(dgt.genome);
    const result_set& po(dgt.poly);

    os << std::setprecision(6) << std::fixed;

    os << ge.snp_qphred
       << '\t' << DIGT::label(ge.max_gt)
       << '\t' << ge.max_gt_qphred
       << '\t' << DIGT::label(po.max_gt)
       << '\t' << po.max_gt_qphred;

    if (opt.is_print_used_allele_counts) {
        pi.print_known_counts(os,opt.used_allele_count_min_qscore);
    }

    if (dgt.is_snp) {
        os << '\t' << dgt.sb
           << '\t' << hpol;
    }

    if (opt.is_print_all_poly_gt) {
        for (unsigned gt(0); gt<DIGT::SIZE; ++gt) {
#if 1

            os << '\t' << po.pprob[gt];
#else

            os << '\t' << error_prob_to_qphred(prob_comp(po.pprob,po.pprob+DIGT::SIZE,gt));
#endif
        }
    }

    os.unsetf(std::ios::fixed);
}
