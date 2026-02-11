giraffe_linedata_load(GiLineData* self, const cxchar* filename)
{

    cxsize extension = 1;

    cpl_table* lines = NULL;

    cpl_propertylist* p = NULL;


    if (self == NULL || filename == NULL) {
        return -1;
    }

    _giraffe_linedata_clear(self);


    giraffe_error_push();

    p = cpl_propertylist_load(filename, 0);

    if (p == NULL) {
        return 1;
    }

    if (cpl_propertylist_has(p, GIALIAS_WSOL_LMNAME) == 0) {
        return 1;
    }
    else {

        self->model = cx_strdup(cpl_propertylist_get_string(p,
            GIALIAS_WSOL_LMNAME));

    }

    if (cpl_error_get_code() != CPL_ERROR_NONE) {

        if (p != NULL) {
            cpl_propertylist_delete(p);
            p = NULL;
        }

        return 1;

    }

    giraffe_error_pop();

    cpl_propertylist_delete(p);
    p = NULL;


    lines = cpl_table_load(filename, extension, 0);

    if (lines == NULL) {
        _giraffe_linedata_clear(self);
        return 2;
    }

    if (cpl_table_has_column(lines, "WLEN") == FALSE) {
        _giraffe_linedata_clear(self);
        return 2;
    }
    else {

        const cxdouble* lambda = cpl_table_get_data_double(lines, "WLEN");

        self->nlines = cpl_table_get_nrow(lines);

        self->ignore = cx_calloc(self->nlines, sizeof(cxint));
        self->wavelength = cx_malloc(self->nlines * sizeof(cxdouble));

        memcpy(self->wavelength, lambda, self->nlines * sizeof(cxdouble));
    }

    ++extension;

    self->status = cpl_image_load(filename, CPL_TYPE_INT, 0, extension);

    if (self->status == NULL) {
        _giraffe_linedata_clear(self);
        return 2;
    }

    self->nfibers = cpl_image_get_size_x(self->status);

    ++extension;


    p = cpl_propertylist_load(filename, extension);


    while ((p != NULL) && (extension < 22)) {

        const cxchar* name = cpl_propertylist_get_string(p, GIALIAS_EXTNAME);

        if (name == NULL) {
            cpl_propertylist_delete(p);
            p = NULL;

            _giraffe_linedata_clear(self);

            return 3;
        }
        else {

            cpl_image* buffer = cpl_image_load(filename, CPL_TYPE_DOUBLE,
                                               0, extension);

            if ((cpl_image_get_size_x(buffer) != self->nfibers) ||
                (cpl_image_get_size_y(buffer) != self->nlines)) {

                cpl_image_delete(buffer);
                buffer = NULL;

                cpl_propertylist_delete(p);
                p = NULL;

                _giraffe_linedata_clear(self);

                return 3;

            }

            cx_map_insert(self->values, cx_strdup(name), buffer);

        }

        ++extension;

        cpl_propertylist_delete(p);
        p = cpl_propertylist_load(filename, extension);

    }

    cpl_propertylist_delete(p);
    p = NULL;

    return 0;

}
