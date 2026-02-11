get_read_align_strand_end_skip(const bam_seq& bseq,
                               unsigned& end_skip) {

    unsigned read_end(bseq.size());

    while (read_end>0) {
        if (bseq.get_char(read_end-1)=='N') read_end--;
        else break;
    }

    end_skip=bseq.size()-read_end;
}
