amp_scalefac_bands(lame_global_flags const *gfp,
                   gr_info * const cod_info, FLOAT const *distort, FLOAT xrpow[576], int bRefine)
{
    lame_internal_flags *const gfc = gfp->internal_flags;
    int     j, sfb;
    FLOAT   ifqstep34, trigger;
    int     noise_shaping_amp;

    if (cod_info->scalefac_scale == 0) {
        ifqstep34 = 1.29683955465100964055;
    }
    else {
        ifqstep34 = 1.68179283050742922612;
    }


    trigger = 0;
    for (sfb = 0; sfb < cod_info->sfbmax; sfb++) {
        if (trigger < distort[sfb])
            trigger = distort[sfb];
    }

    noise_shaping_amp = gfc->noise_shaping_amp;
    if (noise_shaping_amp == 3) {
        if (bRefine == 1)
            noise_shaping_amp = 2;
        else
            noise_shaping_amp = 1;
    }
    switch (noise_shaping_amp) {
    case 2:

        break;

    case 1:

        if (trigger > 1.0)
            trigger = pow(trigger, .5);
        else
            trigger *= .95;
        break;

    case 0:
    default:

        if (trigger > 1.0)
            trigger = 1.0;
        else
            trigger *= .95;
        break;
    }

    j = 0;
    for (sfb = 0; sfb < cod_info->sfbmax; sfb++) {
        int const width = cod_info->width[sfb];
        int     l;
        j += width;
        if (distort[sfb] < trigger)
            continue;

        if (gfc->substep_shaping & 2) {
            gfc->pseudohalf[sfb] = !gfc->pseudohalf[sfb];
            if (!gfc->pseudohalf[sfb] && gfc->noise_shaping_amp == 2)
                return;
        }
        cod_info->scalefac[sfb]++;
        for (l = -width; l < 0; l++) {
            xrpow[j + l] *= ifqstep34;
            if (xrpow[j + l] > cod_info->xrpow_max)
                cod_info->xrpow_max = xrpow[j + l];
        }

        if (gfc->noise_shaping_amp == 2)
            return;
    }
}
