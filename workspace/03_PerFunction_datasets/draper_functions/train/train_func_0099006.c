syncinfo (dca_state_t * state, int * flags,
                     int * sample_rate, int * bit_rate, int * frame_length)
{
    int frame_size;


    bitstream_get (state, 32);

    bitstream_get (state, 1);

    bitstream_get (state, 5);

    bitstream_get (state, 1);

    *frame_length = (bitstream_get (state, 7) + 1) * 32;
    if (*frame_length < 6 * 32) return 0;
    frame_size = bitstream_get (state, 14) + 1;
    if (frame_size < 96) return 0;
    if (!state->word_mode) frame_size = frame_size * 8 / 14 * 2;


    *flags = bitstream_get (state, 6);
    if (*flags > 63)
        return 0;

    *sample_rate = bitstream_get (state, 4);
    if ((size_t)*sample_rate >= sizeof (dca_sample_rates) / sizeof (int))
        return 0;
    *sample_rate = dca_sample_rates[ *sample_rate ];
    if (!*sample_rate) return 0;

    *bit_rate = bitstream_get (state, 5);
    if ((size_t)*bit_rate >= sizeof (dca_bit_rates) / sizeof (int))
        return 0;
    *bit_rate = dca_bit_rates[ *bit_rate ];
    if (!*bit_rate) return 0;


    bitstream_get (state, 10);
    if (bitstream_get (state, 2)) *flags |= DCA_LFE;

    return frame_size;
}
