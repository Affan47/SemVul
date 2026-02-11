mh_set_rtc(byte * out, int chunk_size, int num_bits)
{
    int i, n, code_length, num_fills;

    code_length = 0;


    num_fills = (EOL_SIZE * 6 + (num_bits % 8)) % 8;
    if (num_fills != 0) {
        for (i = 0; i < 8 - num_fills; i++) {
            if ((n = mh_write_to_buffer(out, chunk_size, num_bits + code_length,
                                        fill)) == 0)
                return 0;
            code_length += n;
        }
    }

    for (i = 0; i < 6; i++) {
        if ((n = mh_write_to_buffer(out, chunk_size, num_bits + code_length,
                                    eol)) == 0)
            return 0;
        code_length += n;
    }

    return code_length;
}
