cpl_bivector_wrap_all_but_first(cpl_bivector * self)
{

    const cpl_size n = cpl_bivector_get_size(self);
    cpl_vector   * xvec;
    cpl_vector   * yvec;


    cpl_ensure(self != NULL, CPL_ERROR_NULL_INPUT,    NULL);
    cpl_ensure(n    >  1,    CPL_ERROR_ILLEGAL_INPUT, NULL);

    xvec = cpl_vector_wrap(n-1, 1 + cpl_bivector_get_x_data(self));
    yvec = cpl_vector_wrap(n-1, 1 + cpl_bivector_get_y_data(self));

    return cpl_bivector_wrap_vectors(xvec, yvec);
}
