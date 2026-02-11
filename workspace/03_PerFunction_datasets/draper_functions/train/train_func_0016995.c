refine_cbp_chr422(jxr_image_t image, struct wbitstream*str, int diff_cbp, int block)
{
    static const int shift_mask[4] = {0, 1, 4, 5};
    int bits = diff_cbp >> shift_mask[block];
    switch (bits & 5) {
        case 0:
            assert(0);
            break;
        case 1:
            _jxr_wbitstream_uint1(str, 1);
            break;
        case 4:
            _jxr_wbitstream_uint2(str, 1);
            break;
        case 5:
            _jxr_wbitstream_uint2(str, 0);
            break;
    }
}
