store_interleave_chroma( pixel *dst, int i_dst, pixel *srcu, pixel *srcv, int height )
{
    for( int y=0; y<height; y++, dst+=i_dst, srcu+=FDEC_STRIDE, srcv+=FDEC_STRIDE )
        for( int x=0; x<8; x++ )
        {
            dst[2*x]   = srcu[x];
            dst[2*x+1] = srcv[x];
        }
}
