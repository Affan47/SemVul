w_BLOCK_FLEXBITS(jxr_image_t image, struct wbitstream*str,
                             unsigned tx, unsigned ty,
                             unsigned mx, unsigned my,
                             unsigned ch, unsigned bl, unsigned model_bits)
{
    const int transpose444 [16] = {0, 4, 8,12,
        1, 5, 9,13,
        2, 6,10,14,
        3, 7,11,15 };
    unsigned flexbits_left = model_bits;
    if (image->trim_flexbits > flexbits_left)
        flexbits_left = 0;
    else
        flexbits_left -= image->trim_flexbits;

    DEBUG(" BLOCK_FLEXBITS: flexbits_left=%u (model=%u, trim=%u) block=%u bitpos=%zu\n",
        flexbits_left, model_bits, image->trim_flexbits, bl, _jxr_wbitstream_bitpos(str));

    if (flexbits_left > 0) {
        int idx;
        for (idx = 1 ; idx < 16 ; idx += 1) {
            int idx_trans = transpose444[idx];
            w_DECODE_FLEX(image, str, tx, mx, ch, bl, idx_trans-1, flexbits_left);
        }
    }

    DEBUG(" BLOCK_FLEXBITS done\n");
}
