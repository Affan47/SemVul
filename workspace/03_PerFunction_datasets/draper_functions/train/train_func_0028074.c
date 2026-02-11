x264_predict_8x8c_p_c( pixel *src )
{
    int H = 0, V = 0;

    for( int i = 0; i < 4; i++ )
    {
        H += ( i + 1 ) * ( src[4+i - FDEC_STRIDE] - src[2 - i -FDEC_STRIDE] );
        V += ( i + 1 ) * ( src[-1 +(i+4)*FDEC_STRIDE] - src[-1+(2-i)*FDEC_STRIDE] );
    }

    int a = 16 * ( src[-1+7*FDEC_STRIDE] + src[7 - FDEC_STRIDE] );
    int b = ( 17 * H + 16 ) >> 5;
    int c = ( 17 * V + 16 ) >> 5;
    int i00 = a -3*b -3*c + 16;

    for( int y = 0; y < 8; y++ )
    {
        int pix = i00;
        for( int x = 0; x < 8; x++ )
        {
            src[x] = x264_clip_pixel( pix>>5 );
            pix += b;
        }
        src += FDEC_STRIDE;
        i00 += c;
    }
}
