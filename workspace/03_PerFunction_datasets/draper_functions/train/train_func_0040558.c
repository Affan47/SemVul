trans_sweep(rb_econv_t *ec,
    const unsigned char **input_ptr, const unsigned char *input_stop,
    unsigned char **output_ptr, unsigned char *output_stop,
    int flags,
    int start)
{
    int try;
    int i, f;

    const unsigned char **ipp, *is, *iold;
    unsigned char **opp, *os, *oold;
    rb_econv_result_t res;

    try = 1;
    while (try) {
        try = 0;
        for (i = start; i < ec->num_trans; i++) {
            rb_econv_elem_t *te = &ec->elems[i];

            if (i == 0) {
                ipp = input_ptr;
                is = input_stop;
            }
            else {
                rb_econv_elem_t *prev_te = &ec->elems[i-1];
                ipp = (const unsigned char **)&prev_te->out_data_start;
                is = prev_te->out_data_end;
            }

            if (i == ec->num_trans-1) {
                opp = output_ptr;
                os = output_stop;
            }
            else {
                if (te->out_buf_start != te->out_data_start) {
                    ssize_t len = te->out_data_end - te->out_data_start;
                    ssize_t off = te->out_data_start - te->out_buf_start;
                    MEMMOVE(te->out_buf_start, te->out_data_start, unsigned char, len);
                    te->out_data_start = te->out_buf_start;
                    te->out_data_end -= off;
                }
                opp = &te->out_data_end;
                os = te->out_buf_end;
            }

            f = flags;
            if (ec->num_finished != i)
                f |= ECONV_PARTIAL_INPUT;
            if (i == 0 && (flags & ECONV_AFTER_OUTPUT)) {
                start = 1;
                flags &= ~ECONV_AFTER_OUTPUT;
            }
            if (i != 0)
                f &= ~ECONV_AFTER_OUTPUT;
            iold = *ipp;
            oold = *opp;
            te->last_result = res = rb_transcoding_convert(te->tc, ipp, is, opp, os, f);
            if (iold != *ipp || oold != *opp)
                try = 1;

            switch (res) {
              case econv_invalid_byte_sequence:
              case econv_incomplete_input:
              case econv_undefined_conversion:
              case econv_after_output:
                return i;

              case econv_destination_buffer_full:
              case econv_source_buffer_empty:
                break;

              case econv_finished:
                ec->num_finished = i+1;
                break;
            }
        }
    }
    return -1;
}
