t1_hinter__vstem3(t1_hinter * self, fixed y0, fixed y1, fixed y2, fixed y3, fixed y4, fixed y5)
{   int code;

    if (self->disable_hinting)
        return 0;
    code = t1_hinter__stem(self, vstem, 1, y0, y1, 3);
    if (code < 0)
        return code;
    code = t1_hinter__stem(self, vstem, 2, y2, y3, 3);
    if (code < 0)
        return code;
    return t1_hinter__stem(self, vstem, 3, y4, y5, 3);
}
