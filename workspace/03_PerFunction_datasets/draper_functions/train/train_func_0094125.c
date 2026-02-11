giraffe_cube_create(cxsize width, cxsize height, cxsize depth, cxdouble* data)
{

    GiCube* self = _giraffe_cube_new();


    _giraffe_cube_set_size(self, width, height, depth);

    if (self->size == 0) {
        _giraffe_cube_delete(self);
        return NULL;
    }

    if (data != NULL) {
        self->pixels = data;
    }
    else {
        self->pixels = cx_calloc(self->size, sizeof(cxdouble));
    }

    cx_assert(self->pixels != NULL);


    giraffe_error_push();

    _giraffe_cube_init_planes(self);

    if (cpl_error_get_code() != CPL_ERROR_NONE) {
        _giraffe_cube_delete(self);
        return NULL;
    }

    giraffe_error_pop();

    return self;

}
