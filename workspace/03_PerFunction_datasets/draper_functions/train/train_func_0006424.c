test_indel_placement(const indel_key ik,
                     const pos_t read_start_pos = 0) {

    const pos_t ref_start_pos(1000);
    const bool is_fwd_strand(true);
    const unsigned read_length(100);

    indel_set_t iset;
    const indel_key ikfixed(1075,INDEL::DELETE,1);
    iset.insert(ikfixed);
    iset.insert(ik);

    return make_start_pos_alignment(ref_start_pos,read_start_pos,is_fwd_strand,read_length,iset);
}
