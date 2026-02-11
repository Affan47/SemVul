down_core32(gx_downscaler_t *ds,
                        byte            *outp,
                        byte            *in_buffer,
                        int              row,
                        int              plane,
                        int              span)
{
    int   x, xx, y, value;
    int   pad_white;
    byte *inp;
    int   width  = ds->width;
    int   awidth = ds->awidth;
    int   factor = ds->factor;
    int   div    = factor*factor;

    pad_white = (awidth - width) * factor * 4;
    if (pad_white < 0)
        pad_white = 0;

    if (pad_white)
    {
        inp = in_buffer + width*factor*4;
        for (y = factor; y > 0; y--)
        {
            memset(inp, 0xFF, pad_white);
            inp += span;
        }
    }

    inp = in_buffer;
    {

        const int back  = span * factor - 4;
        const int back2 = factor * 4 - 1;
        for (x = awidth; x > 0; x--)
        {

            value = 0;
            for (xx = factor; xx > 0; xx--)
            {
                for (y = factor; y > 0; y--)
                {
                    value += *inp;
                    inp += span;
                }
                inp -= back;
            }
            inp -= back2;
            *outp++ = (value+(div>>1))/div;

            value = 0;
            for (xx = factor; xx > 0; xx--)
            {
                for (y = factor; y > 0; y--)
                {
                    value += *inp;
                    inp += span;
                }
                inp -= back;
            }
            inp -= back2;
            *outp++ = (value+(div>>1))/div;

            value = 0;
            for (xx = factor; xx > 0; xx--)
            {
                for (y = factor; y > 0; y--)
                {
                    value += *inp;
                    inp += span;
                }
                inp -= back;
            }
            inp -= back2;
            *outp++ = (value+(div>>1))/div;

            value = 0;
            for (xx = factor; xx > 0; xx--)
            {
                for (y = factor; y > 0; y--)
                {
                    value += *inp;
                    inp += span;
                }
                inp -= back;
            }
            inp -= 3;
            *outp++ = (value+(div>>1))/div;
        }
    }
}
