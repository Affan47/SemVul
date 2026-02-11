HLStoRGB(HLS hls)
{
    RGB rgb;
    float m1, m2;

    if (hls.l <= 0.5) {
        m2 = hls.l * (1.0 + hls.s);
    }
    else {
        m2 = hls.l + hls.s - hls.l * hls.s;
    }
    m1 = 2.0 * hls.l - m2;
    rgb.r = value(m1, m2, hls.h + 120.0);
    rgb.g = value(m1, m2, hls.h);
    rgb.b = value(m1, m2, hls.h - 120.0);

    return (rgb);
}
