sub8x8_dct8( dctcoef dct[64], pixel *pix1, pixel *pix2 )
{
    dctcoef tmp[64];

    pixel_sub_wxh( tmp, 8, pix1, FENC_STRIDE, pix2, FDEC_STRIDE );

#define SRC(x) tmp[x*8+i]
#define DST(x) tmp[x*8+i]
    for( int i = 0; i < 8; i++ )
        DCT8_1D
#undef SRC
#undef DST

#define SRC(x) tmp[i*8+x]
#define DST(x) dct[x*8+i]
    for( int i = 0; i < 8; i++ )
        DCT8_1D
#undef SRC
#undef DST
}
