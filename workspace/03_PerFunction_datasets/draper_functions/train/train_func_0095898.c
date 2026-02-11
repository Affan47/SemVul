t1_hinter__adjust_stem_hints_by_missed_flex(t1_hinter * self, t1_glyph_space_coord g0,
                                                         t1_glyph_space_coord gm, int k)
{


    t1_glyph_space_coord gg = g0;
    int i;

    if (gm < g0) {
        g0 ^= gm; gm ^= g0; g0 ^= gm;
    }
    for (i = 0; i < self->hint_count; i++)
        if (!k == (self->hint[i].type != hstem)) {
            t1_hint *hint = &self->hint[i];

            if (g0 <= hint->g0 && hint->g0 <= gm)
                hint->g0 = hint->ag0 = gg;
            if (g0 <= hint->g1 && hint->g1 <= gm)
                hint->g1 = hint->ag1 = gg;
        }
}
