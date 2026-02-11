down_core8_4(gx_downscaler_t *ds,
                         byte            *outp,
                         byte            *in_buffer,
                         int              row,
                         int              plane,
                         int              span)
{
    int   x;
    int   pad_white;
    byte *inp;
    int   width  = ds->width;
    int   awidth = ds->awidth;

    pad_white = (awidth - width) * 4;
    if (pad_white < 0)
        pad_white = 0;

    if (pad_white)
    {
        inp = in_buffer + width*4;
        for (x = 4; x > 0; x--)
        {
            memset(inp, 0xFF, pad_white);
            inp += span;
        }
    }

    inp = in_buffer;


    for (x = awidth; x > 0; x--)
    {
        *outp++ = (inp[0     ] + inp[       1] + inp[       2] + inp[       3] +
                   inp[span  ] + inp[span  +1] + inp[span  +2] + inp[span  +3] +
                   inp[span*2] + inp[span*2+1] + inp[span*2+2] + inp[span*2+3] +
                   inp[span*3] + inp[span*3+1] + inp[span*3+2] + inp[span*3+3] +
                   8)>>4;
        inp += 4;
    }
}
