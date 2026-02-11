edit_bam_read_and_quality(const char* read,
                          const uint8_t* qual,
                          bam1_t& br) {

    const int new_len(strlen(read));
    const int old_size(seq_size(br.core.l_qseq));
    const int new_size(seq_size(new_len));
    const int delta(new_size-old_size);

    if (0 != delta) {
        const int end(bam1_aux(&br)-br.data);
        change_bam_data_segment_len(end,delta,br);
    }
    br.core.l_qseq = new_len;

    uint8_t* p(bam1_seq(&br));
    memset(p,0,(new_len+1)/2);
    for (int i(0); i<new_len; ++i) {
        p[i/2] |= get_bam_seq_code(read[i]) << 4*(1-i%2);
    }

    memcpy(bam1_qual(&br),qual,new_len);
}
