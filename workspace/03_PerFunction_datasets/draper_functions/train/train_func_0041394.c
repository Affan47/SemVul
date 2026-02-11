t1_hinter__compute_opposite_stem_coords(t1_hinter * self)
{   int i;

    for (i = 0; i < self->hint_count; i++)
        if ((self->hint[i].type == vstem || self->hint[i].type == hstem)) {
            t1_glyph_space_coord ag0 = self->hint[i].ag0;
            t1_glyph_space_coord ag1 = self->hint[i].ag1;
            enum t1_align_type aligned0 = self->hint[i].aligned0;
            enum t1_align_type aligned1 = self->hint[i].aligned1;
            t1_glyph_space_coord gw;

            gw = any_abs(self->hint[i].g1 - self->hint[i].g0);
            t1_hinter__align_stem_width(self, &gw, &self->hint[i]);
            if (self->hint[i].g1 - self->hint[i].g0 < 0)
                gw = -gw;
            if (aligned0 > aligned1)
                ag1 = ag0 + gw;
            else if (aligned0 < aligned1)
                ag0 = ag1 - gw;
            else {
                t1_glyph_space_coord d0 = any_abs(ag0 - self->hint[i].g0);
                t1_glyph_space_coord d1 = any_abs(ag1 - self->hint[i].g1);

                if (aligned0 == topzn || aligned1 == topzn)
                    if (gw > 0)
                        ag0 = ag1 - gw;
                    else
                        ag1 = ag0 + gw;
                else if (aligned0 == botzn || aligned1 == botzn)
                    if (gw < 0)
                        ag0 = ag1 - gw;
                    else
                        ag1 = ag0 + gw;
                else if (self->hint[i].type == hstem &&
                        min(any_abs(self->hint[i].g0 - self->ymid), any_abs(self->hint[i].g1 - self->ymid)) >
                        (self->ymax - self->ymin) / 5) {
                    if ((self->hint[i].g1 + self->hint[i].g0) / 2 > self->ymid)
                        ag0 = ag1 - gw;
                    else
                        ag1 = ag0 + gw;
                } else {
                    if (d0 < d1)
                        ag1 = ag0 + gw;
                    else
                        ag0 = ag1 - gw;
                }
            }
            self->hint[i].ag0 = ag0;
            self->hint[i].ag1 = ag1;
        }
}
