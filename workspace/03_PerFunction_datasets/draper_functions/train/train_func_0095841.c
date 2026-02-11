t1_hinter__simplify_representation(t1_hinter * self)
{   int i, j;
    int last_pole = self->pole_count - 1;
    int primary_hint_count = self->primary_hint_count;

    if (last_pole > 1 && self->pole[last_pole -1].type == closepath)
        last_pole -= 2;
    if (self->pole_count <= 1)
        return;


    if (!self->grid_fit_x || !self->grid_fit_y) {
        for (i = j = 0; i < self->hint_count; i++)
            if ((self->hint[i].type == vstem && !self->grid_fit_x) ||
                (self->hint[i].type == hstem && !self->grid_fit_y)) {
                if (i < primary_hint_count)
                    self->primary_hint_count--;
                continue;
            } else {
                if (i != j)
                    self->hint[j] = self->hint[i];
                j++;
            }
        self->hint_count = j;
    }
    for (i = 0; i < self->hint_range_count; i++) {
        t1_hint_range *hint_range = &self->hint_range[i];

        j = hint_range->beg_pole;
        if (self->pole[j].type == closepath)
            hint_range->beg_pole = ++j;
        else {
            if (self->pole[j].type == offcurve)
                hint_range->beg_pole = --j;
            if (self->pole[j].type == offcurve)
                hint_range->beg_pole = --j;
        }
        j = hint_range->end_pole;
        if (j == -1)
            hint_range->end_pole = j = last_pole;
        if (self->pole[j].type == offcurve)
            hint_range->end_pole = ++j;
        if (self->pole[j].type == offcurve)
            hint_range->end_pole = ++j;
    }


    for (i = 0; i <= self->contour_count; i++)
        if (self->pole[self->contour[i]].type == moveto)
            self->pole[self->contour[i]].type = oncurve;


    for (j = 0; j < self->hint_range_count; j++) {
        int beg_pole = self->hint_range[j].beg_pole;
        int contour_index = self->pole[beg_pole].contour_index;
        int contour_beg_pole = self->contour[contour_index];

        if (beg_pole > contour_beg_pole && beg_pole < last_pole)
            self->hint_range[j].beg_pole = t1_hinter__segment_beg(self, beg_pole);
    }
}
