ff_mpeg4audio_get_config(MPEG4AudioConfig *c, const uint8_t *buf, int buf_size)
{
    GetBitContext gb;
    int specific_config_bitindex;

    init_get_bits(&gb, buf, buf_size*8);
    c->object_type = get_object_type(&gb);
    c->sample_rate = get_sample_rate(&gb, &c->sampling_index);
    c->chan_config = get_bits(&gb, 4);
    c->sbr = -1;
    if (c->object_type == 5) {
        c->ext_object_type = c->object_type;
        c->sbr = 1;
        c->ext_sample_rate = get_sample_rate(&gb, &c->ext_sampling_index);
        c->object_type = get_object_type(&gb);
    } else
        c->ext_object_type = 0;

    specific_config_bitindex = get_bits_count(&gb);

    if (c->ext_object_type != 5) {
        int bits_left = buf_size*8 - specific_config_bitindex;
        for (; bits_left > 15; bits_left--) {
            if (show_bits(&gb, 11) == 0x2b7) {
                get_bits(&gb, 11);
                c->ext_object_type = get_object_type(&gb);
                if (c->ext_object_type == 5 && (c->sbr = get_bits1(&gb)) == 1)
                    c->ext_sample_rate = get_sample_rate(&gb, &c->ext_sampling_index);
                break;
            } else
                get_bits1(&gb);
        }
    }
    return specific_config_bitindex;
}
