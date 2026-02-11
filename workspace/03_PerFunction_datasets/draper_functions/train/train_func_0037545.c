ATHmdct(SessionConfig_t const *cfg, FLOAT f)
{
    FLOAT   ath;

    ath = ATHformula(cfg, f);

    if (cfg->vbr == vbr_mt && cfg->ATHfixpoint > 0) {
        ath -= cfg->ATHfixpoint;
    }
    else {
        ath -= NSATHSCALE;
    }


    ath = pow(10.0, ath / 10.0 + cfg->ATHlower);
    return ath;
}
