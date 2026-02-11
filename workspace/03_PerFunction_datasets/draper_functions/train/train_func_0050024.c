process_contig(const starling_options& client_opt,
               const reference_contig_segment& ref,
               const grouper_contig& ctg,
               starling_pos_processor_base& sppr,
               const unsigned sample_no,
               const char* sample_label) {

    contig_no++;

#ifdef DEBUG_STARLING
    log_os << "contig_no: " << contig_no << "\n";
    log_os << "contig: " << ctg;
#endif

    if (! is_valid_seq(ctg.seq.c_str())) {
        log_os << "ERROR: invalid sequence in contig: " << ctg << "\n";
        exit(EXIT_FAILURE);
    }

    static const INDEL_ALIGN_TYPE::index_t iat(INDEL_ALIGN_TYPE::CONTIG);
    const string_bam_seq bseq(ctg.seq);
    try {
        static const std::pair<bool,bool> edge_pin(std::make_pair(false,false));
        add_alignment_indels_to_sppr(client_opt.max_indel_size,ref,ctg,bseq,sppr,iat,contig_no,sample_no, edge_pin);
    } catch (...) {
        log_os << "\nException caught in add_alignment_indels_to_sppr() while processing contig";
        if (NULL != sample_label) log_os << " from sample '" << sample_label << "'";
        log_os << ":\n" << ctg;
        throw;
    }
}
