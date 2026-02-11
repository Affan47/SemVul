init(struct bs2b *bs2b)
{
    double Fc_lo, Fc_hi;
    double G_lo,  G_hi;
    double x;

    if ((bs2b->srate > 192000) || (bs2b->srate < 2000))
        bs2b->srate = BS2B_DEFAULT_SRATE;

    switch(bs2b->level)
    {
    case BS2B_LOW_CLEVEL:
        Fc_lo = 360.0;
        Fc_hi = 501.0;
        G_lo  = 0.398107170553497;
        G_hi  = 0.205671765275719;
        break;

    case BS2B_MIDDLE_CLEVEL:
        Fc_lo = 500.0;
        Fc_hi = 711.0;
        G_lo  = 0.459726988530872;
        G_hi  = 0.228208484414988;
        break;

    case BS2B_HIGH_CLEVEL:
        Fc_lo = 700.0;
        Fc_hi = 1021.0;
        G_lo  = 0.530884444230988;
        G_hi  = 0.250105790667544;
        break;

    case BS2B_LOW_ECLEVEL:
        Fc_lo = 360.0;
        Fc_hi = 494.0;
        G_lo  = 0.316227766016838;
        G_hi  = 0.168236228897329;
        break;

    case BS2B_MIDDLE_ECLEVEL:
        Fc_lo = 500.0;
        Fc_hi = 689.0;
        G_lo  = 0.354813389233575;
        G_hi  = 0.187169483835901;
        break;

    default:
        bs2b->level = BS2B_HIGH_ECLEVEL;

        Fc_lo = 700.0;
        Fc_hi = 975.0;
        G_lo  = 0.398107170553497;
        G_hi  = 0.205671765275719;
        break;
    }


    x           = exp(-2.0 * M_PI * Fc_lo / bs2b->srate);
    bs2b->b1_lo = x;
    bs2b->a0_lo = G_lo * (1.0 - x);

    x           = exp(-2.0 * M_PI * Fc_hi / bs2b->srate);
    bs2b->b1_hi = x;
    bs2b->a0_hi = 1.0 - G_hi * (1.0 - x);
    bs2b->a1_hi = -x;

    bs2b->gain  = 1.0f / (float)(1.0 - G_hi + G_lo);
}
