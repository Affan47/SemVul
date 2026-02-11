sequence(ALI_NORM_SEQUENCE *ref_seq)
{
    int ins_counter;
    int begin_flag = 0, undefined_flag;
    unsigned long map_pos, seq_pos;
    unsigned char *seq, *seq_buffer;

    seq_buffer = (unsigned char *) CALLOC((unsigned int)
                                          (last_ref_base - first_ref_base + insert_counter + 1),
                                          sizeof(unsigned char));

    if (seq_buffer == 0)
        ali_fatal_error("Out of memory");

    seq = seq_buffer;
    seq_pos = 0;
    undefined_flag = 0;
    ins_counter = 0;
    for (map_pos = 0; map_pos <= last_seq_base - first_seq_base; map_pos++) {
        if (!undefined_flag)
            begin_flag = ref_seq->is_begin(first_seq_base + map_pos);
        if (!(((*undefined)[map_pos/8]>>(7-(map_pos%8))) & 0x01)) {
            for (;seq_pos < (unsigned long)((*mapping)[map_pos] + ins_counter); seq_pos++) {
                if (begin_flag)
                    *seq++ = ALI_DOT_CODE;
                else
                    *seq++ = ALI_GAP_CODE;
            }
            *seq++ = ref_seq->base(first_seq_base + map_pos);
            seq_pos++;
            undefined_flag = 0;
        }
        else {
            undefined_flag = 1;
        }
        if ((*inserted)[map_pos/8]>>(7-(map_pos%8)) & 0x01)
            ins_counter++;
    }

    begin_flag = ref_seq->is_begin(first_seq_base + map_pos);
    for (;seq_pos <= last_ref_base - first_ref_base + ins_counter;seq_pos++) {
        if (begin_flag)
            *seq++ = ALI_DOT_CODE;
        else
            *seq++ = ALI_GAP_CODE;
    }

    return new ALI_SEQUENCE(ref_seq->name(),seq_buffer,
                            last_ref_base - first_ref_base + insert_counter + 1);
}
