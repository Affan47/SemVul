ff_h264_lowres_idct_add_c(uint8_t *dst, int stride, DCTELEM *block){
    idct_internal(dst, block, stride, 8, 3, 1);
}
