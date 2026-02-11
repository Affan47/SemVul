rgb2pixel( unsigned int r,
           unsigned int g,
           unsigned int b )
{
    FL_State *s = fl_state + fl_vmode;


    if ( s->rbits < 8 )
    {
        r >>= 8 - s->rbits;
        g >>= 8 - s->gbits;
        b >>= 8 - s->bbits;
    }
    else if ( s->rbits > 8 )
    {
        r <<= 8 - s->rbits;
        g <<= 8 - s->gbits;
        b <<= 8 - s->bbits;
    }

    return   ( ( ( unsigned long ) r << s->rshift ) & s->rmask )
           | ( ( ( unsigned long ) g << s->gshift ) & s->gmask )
           | ( ( ( unsigned long ) b << s->bshift ) & s->bmask );
}
