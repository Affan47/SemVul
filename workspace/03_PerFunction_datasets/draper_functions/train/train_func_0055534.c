zigzag_interleave_8x8_cavlc( dctcoef *dst, dctcoef *src, uint8_t *nnz )
{
    for( int i = 0; i < 4; i++ )
    {
        int nz = 0;
        for( int j = 0; j < 16; j++ )
        {
            nz |= src[i+j*4];
            dst[i*16+j] = src[i+j*4];
        }
        nnz[(i&1) + (i>>1)*8] = !!nz;
    }
}
