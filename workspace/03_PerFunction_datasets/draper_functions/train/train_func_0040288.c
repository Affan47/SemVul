giraffe_chebyshev2d_new(cxint xorder, cxint yorder)
{

    GiChebyshev2D *self = cx_calloc(1, sizeof *self);


    if (self) {

        self->xorder = xorder;
        self->yorder = yorder;

        self->coeffs = cpl_matrix_new((xorder + 1), (yorder + 1));

        if (self->coeffs == NULL) {
            giraffe_chebyshev2d_delete(self);
            return NULL;
        }

    }

    return self;

}
