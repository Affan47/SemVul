bicubicspline_reg_set(
        int nxi, double xi0, double dxi,
        int nyi, double yi0, double dyi,
        double **vi,
        int nso, double *xo, double *yo,
        enum boundary_mode mode)
{
    double *vo = vector(nso);
    double **v2 = blank_matrix(nxi);
    double *vtmp = NULL;
    double *vvtmp = NULL;
    double y1start = 0.0;
    double y1end = 0.0;
    int ix = 0, is = 0, k = 0;


    for (ix=0; ix<nxi; ix++) {
        v2[ix] = spline_reg_init(nyi, dyi, vi[ix], mode, y1start, y1end);
    }

    for (is=0; is<nso; is++) {
        vvtmp = vector(nxi);
        for (k=0; k<nxi; k++) {
            vvtmp[k] = spline_reg_interpolate(nyi, yi0, dyi, vi[k], v2[k], yo[is]);
        }
        vtmp = spline_reg_init(nxi, dxi, vvtmp, mode, y1start, y1end);
        vo[is] = spline_reg_interpolate(nxi, xi0, dxi, vvtmp, vtmp, xo[is]);
        free_vector(vtmp);
        free_vector(vvtmp);
    }
    free_matrix(v2,nxi);

    return vo;
}
