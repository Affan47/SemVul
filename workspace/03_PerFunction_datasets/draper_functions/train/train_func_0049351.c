giraffe_model_evaluate(const GiModel *self, cxdouble *result, cxint *status)
{

    const cxchar *const fctid = "giraffe_model_evaluate";

    cxdouble _result = 0.;
    cxdouble *arg = NULL;
    cxdouble *par = NULL;


    cx_assert(self != NULL);

    arg = cpl_matrix_get_data(self->arguments.values);

    if (arg == NULL) {
        cpl_error_set(fctid, CPL_ERROR_ILLEGAL_INPUT);
        return 2;
    }

    par = cpl_matrix_get_data(self->parameters.values);

    if (par == NULL) {
        cpl_error_set(fctid, CPL_ERROR_ILLEGAL_INPUT);
        return 3;
    }

    giraffe_error_push();

    self->model(&_result, arg, par, self->parameters.count, NULL, NULL);

    if (cpl_error_get_code() != CPL_ERROR_NONE) {

        if (status) {
            *status = 1;
        }

        return 4;

    }

    giraffe_error_pop();

    *result = _result;
    *status = 0;

    return 0;

}
