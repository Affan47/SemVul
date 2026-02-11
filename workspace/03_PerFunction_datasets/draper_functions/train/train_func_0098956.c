giraffe_model_fit(GiModel *self, cpl_matrix *x, cpl_matrix *y,
                  cpl_matrix *sigma)
{

    cxint ndata = 0;


    cx_assert(self != NULL);

    if (x == NULL || y == NULL) {
        return -128;
    }

    if (sigma == NULL) {
        return -128;
    }

    ndata = cpl_matrix_get_nrow(y);

    return _giraffe_model_fit(self, x, y, sigma, ndata, 0, 1);

}
