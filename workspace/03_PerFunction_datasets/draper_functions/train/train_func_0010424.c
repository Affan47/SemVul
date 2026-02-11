apply_vbr_preset(lame_global_flags * gfp, int a, int enforce)
{
    vbr_presets_t const *vbr_preset = get_vbr_preset(lame_get_VBR(gfp));
    float   x = gfp->VBR_q_frac;
    vbr_presets_t p = vbr_preset[a];
    vbr_presets_t q = vbr_preset[a + 1];
    vbr_presets_t const *set = &p;

    NOOP(vbr_q);
    NOOP(quant_comp);
    NOOP(quant_comp_s);
    NOOP(expY);
    LERP(st_lrm);
    LERP(st_s);
    LERP(masking_adj);
    LERP(masking_adj_short);
    LERP(ath_lower);
    LERP(ath_curve);
    LERP(ath_sensitivity);
    LERP(interch);
    NOOP(safejoint);
    LERP(sfb21mod);
    LERP(msfix);
    LERP(minval);
    LERP(ath_fixpoint);

    (void) lame_set_VBR_q(gfp, set->vbr_q);
    SET_OPTION(quant_comp, set->quant_comp, -1);
    SET_OPTION(quant_comp_short, set->quant_comp_s, -1);
    if (set->expY) {
        (void) lame_set_experimentalY(gfp, set->expY);
    }
    SET_OPTION(short_threshold_lrm, set->st_lrm, -1);
    SET_OPTION(short_threshold_s, set->st_s, -1);
    SET_OPTION(maskingadjust, set->masking_adj, 0);
    SET_OPTION(maskingadjust_short, set->masking_adj_short, 0);
    if (lame_get_VBR(gfp) == vbr_mt || lame_get_VBR(gfp) == vbr_mtrh) {
        lame_set_ATHtype(gfp, 5);
    }
    SET_OPTION(ATHlower, set->ath_lower, 0);
    SET_OPTION(ATHcurve, set->ath_curve, -1);
    SET_OPTION(athaa_sensitivity, set->ath_sensitivity, 0);
    if (set->interch > 0) {
        SET_OPTION(interChRatio, set->interch, -1);
    }


    if (set->safejoint > 0) {
        (void) lame_set_exp_nspsytune(gfp, lame_get_exp_nspsytune(gfp) | 2);
    }
    if (set->sfb21mod > 0) {
        int const nsp = lame_get_exp_nspsytune(gfp);
        int const val = (nsp >> 20) & 63;
        if (val == 0) {
            int const sf21mod = (set->sfb21mod << 20) | nsp;
            (void) lame_set_exp_nspsytune(gfp, sf21mod);
        }
    }
    SET__OPTION(msfix, set->msfix, -1);

    if (enforce == 0) {
        gfp->VBR_q = a;
        gfp->VBR_q_frac = x;
    }
    gfp->internal_flags->cfg.minval = set->minval;
    gfp->internal_flags->cfg.ATHfixpoint = set->ath_fixpoint;
}
