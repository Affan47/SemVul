aw_install_xkeys(Display *display) {
    int i;

    awxkeymap_string_2_key_hash = GBS_create_hash(KEYMAX, GB_MIND_CASE);
    awxkeymap_xkey_2_key_hash   = GBS_create_hashi(KEYMAX);


    for (i=0;;++i) {
        if (awxkeymap_modfree[i].xstr_suffix == 0) break;
    }

    const int MODS = 9;

    struct awModDef {
        int         xmod;
        const char *xstr_prefix;
        AW_key_mod  awmod;
    }
    moddef[MODS] = {
        { XK_Shift_L,   "Shift",   AW_KEYMODE_SHIFT },
        { XK_Shift_R,   "Shift",   AW_KEYMODE_SHIFT },
        { XK_Meta_L,    "Meta",    AW_KEYMODE_ALT },
        { XK_Meta_R,    "Meta",    AW_KEYMODE_ALT },
        { XK_Alt_L,     "Alt",     AW_KEYMODE_ALT },
        { XK_Alt_R,     "Alt",     AW_KEYMODE_ALT },
        { XK_Control_L, "Control", AW_KEYMODE_CONTROL },
        { XK_Control_R, "Control", AW_KEYMODE_CONTROL },
        { 0,            0,         AW_KEYMODE_NONE },
    };

    int modfree = i;
    int gensize = modfree*MODS;

    static awXKeymap *generated = 0;

    aw_assert(generated == 0);
    generated = (awXKeymap*)GB_calloc(gensize, sizeof(*generated));

    for (i=0;i<modfree;++i) {
        const awXKeymap_modfree *mf = awxkeymap_modfree+i;
        for (int j = 0; j<MODS; ++j) {
            awXKeymap *km = generated+i*MODS+j;
            awModDef  *md = moddef+j;

            km->xmod  = md->xmod;
            km->xkey  = mf->xkey;
            km->xstr  = md->xstr_prefix ? GBS_global_string_copy("%s-%s", md->xstr_prefix, mf->xstr_suffix) : mf->xstr_suffix;
            km->awmod = md->awmod;
            km->awkey = mf->awkey;
            km->awstr = 0;

            map_awXKey(display, km);
        }
    }


    for (i=0;;++i) {
        if (awxkeymap[i].xstr== (char*)1) break;
        map_awXKey(display, awxkeymap+i);
    }

    aw_assert(mappedKeys<KEYMAX);
}
