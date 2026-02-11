find(int pos) {
    SEC_helix_strand *start_strand = root_loop->get_fixpoint_strand();
    SEC_helix_strand *strand       = start_strand;
    do {
        SEC_region *reg = strand->get_region();
        if (reg->contains_seq_position(pos)) return strand;

        SEC_helix_strand *other_strand = strand->get_other_strand();
        SEC_region       *oreg         = other_strand->get_region();

        SEC_segment *seg;
        if (SEC_region(reg->get_sequence_end(), oreg->get_sequence_start()).contains_seq_position(pos)) {
            seg = other_strand->get_next_segment();
        }
        else {
            if (oreg->contains_seq_position(pos)) return other_strand;
            seg = strand->get_next_segment();
        }

        if (seg->get_region()->contains_seq_position(pos)) return seg;
        strand = seg->get_next_strand();
    }
    while (strand != start_strand);

    return 0;
}
