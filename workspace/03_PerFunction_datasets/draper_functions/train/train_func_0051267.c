giraffe_chebyshev2d_get_order(const GiChebyshev2D *self, cxint *xorder,
                                   cxint *yorder)
{

    cx_assert(self != NULL);

    if (xorder != NULL) {
        *xorder = self->xorder;
    }

    if (yorder != NULL) {
        *yorder = self->yorder;
    }

    return;

}
