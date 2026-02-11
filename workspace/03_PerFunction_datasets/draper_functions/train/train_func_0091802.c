runproc (unsigned long len, bool add)
{
    float t, xx, yy, zz, dxx, dyy, dzz;
    float *in, *out_w, *out_x, *out_y, *out_z;

    xx = _xx;
    yy = _yy;
    zz = _zz;
    calcpar (_port [CTL_AZIM][0], _port [CTL_ELEV][0]);
    dxx = (_xx - xx) / len;
    dyy = (_yy - yy) / len;
    dzz = (_zz - zz) / len;

    in = _port [INP];
    out_w = _port [OUT_W];
    out_x = _port [OUT_X];
    out_y = _port [OUT_Y];
    out_z = _port [OUT_Z];

    while (len--)
    {
	xx += dxx;
	yy += dyy;
	zz += dzz;
        t = *in++;
        *out_w++ = MIN3DB * t;
        *out_x++ = xx * t;
        *out_y++ = yy * t;
        *out_z++ = zz * t;
    }
}
