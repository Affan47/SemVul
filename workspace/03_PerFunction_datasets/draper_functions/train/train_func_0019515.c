get_sfxcount(const char * morph)
{
    if (!morph || !*morph) return 0;
    int n = 0;
    const char * old = morph;
    morph = strstr(morph, MORPH_DERI_SFX);
    if (!morph) morph = strstr(old, MORPH_INFL_SFX);
    if (!morph) morph = strstr(old, MORPH_TERM_SFX);
    while (morph) {
        n++;
        old = morph;
        morph = strstr(morph + 1, MORPH_DERI_SFX);
        if (!morph) morph = strstr(old + 1, MORPH_INFL_SFX);
        if (!morph) morph = strstr(old + 1, MORPH_TERM_SFX);
    }
    return n;
}
