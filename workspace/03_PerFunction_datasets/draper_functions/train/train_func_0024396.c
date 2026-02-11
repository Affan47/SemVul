t1_hinter__setcurrentpoint(t1_hinter * self, fixed xx, fixed yy)
{
    t1_hinter__adjust_matrix_precision(self, xx, yy);
    if (self->FontType != 2) {


        self->cx = xx;
        self->cy = yy;
    } else if (self->cx != xx || self->cy != yy) {


        self->cx = xx;
        self->cy = yy;
    }
}
