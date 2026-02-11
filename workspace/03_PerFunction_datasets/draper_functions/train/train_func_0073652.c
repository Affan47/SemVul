gamma_n (double gamma, int brightness, int contrast,
                      u_char *buf, int bpp, int gamma_mode)
{
    int i;
    double i_gamma = 1.0/gamma;
    int length = 1 << bpp;
    int max = length - 1;
    double mid = max / 2.0;

    for (i = 0;  i < length;  i++)
    {
        int x;
        double val = (i - mid) * (1.0 + contrast / 100.0)
            + (1.0 + brightness / 100.0) * mid;
        val = LIMIT(val, 0, max);
        switch (gamma_mode)
        {
        case GAMMA_16BIT:
            x = LIMIT(65535*pow ((double) val/max, i_gamma) + 0.5, 0, 65535);

            buf[2*i] = (u_char) x;
            buf[2*i + 1] = (u_char) (x >> 8);
            break;
        case GAMMA_12_16BIT:
            buf[2*i] = (u_char) i;
            buf[2*i + 1] = (u_char) (i >> 8);
            break;
        case GAMMA_8BIT:
            buf[i] =
                (u_char) LIMIT(255*pow ((double) val/max, i_gamma) + 0.5, 0, 255);
            break;
        default:
            break;
        }
    }
}
