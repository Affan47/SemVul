cpl_image_fill_window(cpl_image * self,
                                     cpl_size     llx,
                                     cpl_size     lly,
                                     cpl_size     urx,
                                     cpl_size     ury,
                                     double value)
{

    size_t i, j;
    cpl_error_code code = CPL_ERROR_NONE;

    cpl_ensure_code(self != NULL,    CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(llx >= 1,        CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(lly >= 1,        CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(llx <= urx,      CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(lly <= ury,      CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(urx <= self->nx, CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(ury <= self->ny, CPL_ERROR_ILLEGAL_INPUT);

    for (j = (size_t)lly; j <= (size_t)ury; j++) {
        for (i = (size_t)llx; i <= (size_t)urx; i++) {

            code = cpl_image_set(self, (cpl_size)i, (cpl_size)j, value);
            if (code) break;
        }
        if (code) break;
    }

    return code ? cpl_error_set_where_() : CPL_ERROR_NONE;
}
