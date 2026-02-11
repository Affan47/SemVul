t1_hinter__compact_flex(t1_hinter * self, int contour_beg, int contour_end, int i0, int i1, int *pi)
{
    if (i0 > i1) {
        t1_hinter__compact_flex(self, contour_beg, contour_end, i0, contour_end, pi);
        t1_hinter__compact_flex(self, contour_beg, contour_end, contour_beg, i1, pi);
    } else if (i0 < i1) {
        int i, j;
        int s = i1 - i0 - 1;

        for (j = 0; j < self->hint_range_count; j++) {
            if (self->hint_range[j].beg_pole >= i1)
                self->hint_range[j].beg_pole -= s;
            else if (self->hint_range[j].beg_pole > i0)
                self->hint_range[j].beg_pole = i0;
            if (self->hint_range[j].end_pole >= i1)
                self->hint_range[j].end_pole -= s;
            else if (self->hint_range[j].end_pole > i0)
                self->hint_range[j].end_pole = i0;
        }
        if (VD_DRAW_IMPORT) {
            for (i = i0; i <= i1; i++)
                vd_square(self->pole[i].gx, self->pole[i].gy, 7, RGB(0,0,0));
        }
        memmove(&self->pole[i0 + 1], &self->pole[i1], sizeof(*self->pole) * (self->pole_count - i1));
        self->contour[self->contour_count] -= s;
        self->pole_count -= s;
        if (*pi >= i1)
            *pi -= s;
        else if (i0 <= *pi)
            *pi = i0;
    }
}
