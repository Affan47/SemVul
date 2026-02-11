get_htypes_for_indel(const starling_deriv_options& dopt,
                     const starling_read_buffer& rbuff,
                     const reference_contig_segment& ref,
                     const indel_key& ik,
                     const indel_data& id,
                     htype_buffer& hdata) {

    static const bool is_tier2_pass(false);
    static const bool is_use_alt_indel(true);
    static const double include_thresh(0.999);

    typedef indel_data::score_t::const_iterator siter;

    htype_element he;
    siter i(id.read_path_lnp.begin()), i_end(id.read_path_lnp.end());
    for (; i!=i_end; ++i) {
        const align_id_t read_id(i->first);
        const read_path_scores& path_lnp(i->second);
        const read_path_scores pprob(indel_lnp_to_pprob(dopt,path_lnp,is_tier2_pass,is_use_alt_indel));

        if (pprob.indel >= include_thresh) {

            const starling_read* srptr(rbuff.get_read(read_id));


            if (srptr->is_segmented()) {
                log_os << "ERROR: haplotype model does not work for spliced reads\n";
                exit(EXIT_FAILURE);
            }
            const read_segment& rseg(srptr->get_full_segment());

            if (! convert_indel_to_htype(ik,id,rseg,ref,he)) continue;

            hdata.insert_element(he);
        }
    }
}
