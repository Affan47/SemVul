RGBtoHLS( NWT_RGB rgb )
{
    short R, G, B;
    HLS hls;
    unsigned char cMax, cMin;
    short Rdelta, Gdelta, Bdelta;

    R = rgb.r;
    G = rgb.g;
    B = rgb.b;


    cMax = (unsigned char) MAX( MAX(R,G), B );
    cMin = (unsigned char) MIN( MIN(R,G), B );
    hls.l = (((cMax + cMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);

    if( cMax == cMin )
    {
        hls.s = 0;
        hls.h = UNDEFINED;
    }
    else
    {

        if( hls.l <= (HLSMAX / 2) )
            hls.s =
              (((cMax - cMin) * HLSMAX) + ((cMax + cMin) / 2)) / (cMax + cMin);
        else
            hls.s= (((cMax - cMin) * HLSMAX) + ((2 * RGBMAX - cMax - cMin) / 2))
              / (2 * RGBMAX - cMax - cMin);


        Rdelta =
            (((cMax - R) * (HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);
        Gdelta =
            (((cMax - G) * (HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);
        Bdelta =
            (((cMax - B) * (HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);

        if( R == cMax )
            hls.h = Bdelta - Gdelta;
        else if( G == cMax )
            hls.h = (HLSMAX / 3) + Rdelta - Bdelta;
        else
            hls.h = ((2 * HLSMAX) / 3) + Gdelta - Rdelta;

        if( hls.h < 0 )
            hls.h += HLSMAX;
        if( hls.h > HLSMAX )
            hls.h -= HLSMAX;
    }
    return hls;
}
