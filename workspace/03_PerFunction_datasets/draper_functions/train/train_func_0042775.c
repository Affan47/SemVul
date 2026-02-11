pixel_avg_wxh( pixel *dst, int i_dst, pixel *src1, int i_src1, pixel *src2, int i_src2, int width, int height )
{
    for( int y = 0; y < height; y++ )
    {
        for( int x = 0; x < width; x++ )
            dst[x] = ( src1[x] + src2[x] + 1 ) >> 1;
        src1 += i_src1;
        src2 += i_src2;
        dst += i_dst;
    }
}
