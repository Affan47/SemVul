use_family_blues(uint8 *prep_head, GlobalInstrCt *gic) {
    int i, h1, h2, stopat;
    int bs = GetBlueScale(gic->sf);
    int EM = gic->sf->ascent + gic->sf->descent;
    int callargs[3];

    for (i=0; i<gic->bluecnt; i++) {
        if (finite(gic->blues[i].family_base))
        {
            for (stopat=0; stopat<32768; stopat++) {
                h1 = compute_blue_height(gic->blues[i].base, EM, bs, stopat);
                h2 = compute_blue_height(gic->blues[i].family_base, EM, bs, stopat);
                if (abs(h1 - h2) > 1) break;
            }

            callargs[0] = gic->blues[i].family_cvtindex;
            callargs[1] = stopat;
            callargs[2] = 2;

            prep_head = pushnum(prep_head, gic->blues[i].cvtindex);
            *prep_head++ = DUP;
            *prep_head++ = 0x45;
            prep_head = pushnums(prep_head, 3, callargs);
            *prep_head++ = CALL;
            *prep_head++ = 0x44;
        }
    }

    return prep_head;
}
