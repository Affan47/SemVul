cpl_vector_rewrap(cpl_vector * self, cpl_size n, double * data)
{
    void * ptr = NULL;

    if (n <= 0) {
        (void)cpl_error_set_message_(CPL_ERROR_ILLEGAL_INPUT,
                                     "n=%" CPL_SIZE_FORMAT " < 1", n);
    } else if (data == NULL) {
        (void)cpl_error_set_message_(CPL_ERROR_NULL_INPUT, "data");
    } else {

        if (self == NULL) {
            ptr = cpl_malloc(sizeof(cpl_vector));
            self = (cpl_vector*)ptr;
        } else {
            ptr = (double*)self->data;
        }

        self->size = n;
        self->data = data;
    }

    return ptr;
}
