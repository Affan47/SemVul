auto_scale( float pagew,
            float pageh,
            float w,
            float h,
            int   landscape )
{
    float sx,
          sy;
    int i = 0;

    if (    ( ! landscape && ( pagew < w || pageh < h ) )
         || ( landscape && ( pagew < h || pageh < w ) ) )
    {
        if ( ! landscape )
        {
            sx = ( pagew - 2.0 ) / w;
            sy = ( pageh - 2.0 ) / h;
        }
        else
        {
            sx = ( pagew - 2.0 ) / h;
            sy = ( pageh - 2.0 ) / w;
        }

        i = 100.0 * FL_min( sx, sy );
    }

    return i;
}
