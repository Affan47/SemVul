get_half_le(const guchar *p)
{
    gdouble x = p[0]/1024.0 + (p[1] & 0x03)/4.0;
    gint exponent = (p[1] >> 2) & 0x1f;

    if (G_UNLIKELY(exponent == 0x1f)) {

        if (x)
            return 0.0/0.0;
        return (p[1] & 0x80) ? -HUGE_VAL : HUGE_VAL;
    }

    if (exponent)
        x = (1.0 + x)*gwy_powi(2.0, exponent - 15);
    else
        x = x/16384.0;

    return (p[1] & 0x80) ? -x : x;
}
