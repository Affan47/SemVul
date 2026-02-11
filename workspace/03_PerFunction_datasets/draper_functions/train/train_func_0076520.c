normalize_stem(uint8 *prep_head, int xdir, StdStem *stem, GlobalInstrCt *gic) {
    int callargs[3];
    int i;

    stem->stopat = 32767;

    if (stem->snapto != NULL)
    {

        int EM = gic->sf->ascent + gic->sf->descent;

        for (i=7; i<32768; i++) {
            int width_parent = compute_stem_width(xdir, stem->snapto, EM, i);
            int width_me = compute_stem_width(xdir, stem, EM, i);

            if (width_parent != width_me) {
                stem->stopat = i;
                break;
            }
        }


        callargs[0] = stem->snapto->cvtindex;
        callargs[1] = stem->stopat;
        callargs[2] = 2;
        prep_head = pushnums(prep_head, 3, callargs);
        *prep_head++ = CALL;


        if (xdir) {
            prep_head = push2nums(prep_head, 3, 70);
            *prep_head++ = SROUND;
        }
        else prep_head = pushnum(prep_head, 3);

        *prep_head++ = CALL;
    }
    else {

        prep_head = pushnum(prep_head, 3);
        *prep_head++ = CALL;
    }

return prep_head;
}
