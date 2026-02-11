RTjpeg_set_quality(RTjpeg_t *rtj, int *quality)
{
 if (*quality < 1) *quality = 1;
 if (*quality > 255) *quality = 255;
 rtj->Q = *quality;
 RTjpeg_calc_tbls(rtj);
 RTjpeg_dct_init(rtj);
 RTjpeg_idct_init(rtj);
 RTjpeg_quant_init(rtj);

 return 0;
}
