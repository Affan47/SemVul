get_vcf_summary_strings(const indel_key& ik,
                        const indel_data& id,
                        const reference_contig_segment& ref,
                        std::string& vcf_indel_seq,
                        std::string& vcf_ref_seq) {

    if       (ik.is_breakpoint()) {
        if       (ik.type == INDEL::BP_LEFT) {
            copy_ref_subseq(ref,ik.pos-1,ik.pos,vcf_ref_seq);
            vcf_indel_seq = vcf_ref_seq + id.get_insert_seq() + '.';
        } else if (ik.type == INDEL::BP_RIGHT) {
            copy_ref_subseq(ref,ik.pos,ik.pos+1,vcf_ref_seq);
            vcf_indel_seq = '.' + id.get_insert_seq() + vcf_ref_seq;
        } else {
            assert(0);
        }
    } else {
        copy_ref_subseq(ref,ik.pos-1,ik.pos+ik.delete_length(),vcf_ref_seq);
        copy_ref_subseq(ref,ik.pos-1,ik.pos,vcf_indel_seq);
        vcf_indel_seq += id.get_insert_seq();
    }
}
