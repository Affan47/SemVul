cpl_mask_extract_subsample(const cpl_mask *in,
                                     cpl_size        xstep,
                                     cpl_size        ystep)
{
    cpl_size          new_nx, new_ny;
    cpl_mask         *out;
    cpl_binary       *pout;
    const cpl_binary *pin;
    cpl_size          i, j;


    cpl_ensure(in    != NULL, CPL_ERROR_NULL_INPUT,    NULL);
    cpl_ensure(xstep > 0,     CPL_ERROR_ILLEGAL_INPUT, NULL);
    cpl_ensure(ystep > 0,     CPL_ERROR_ILLEGAL_INPUT, NULL);

    new_nx = (in->nx - 1)/xstep + 1;
    new_ny = (in->ny - 1)/ystep + 1;

    out = cpl_mask_new(new_nx, new_ny);
    pin = cpl_mask_get_data_const(in);
    pout = cpl_mask_get_data(out);

    for (j = 0; j < in->ny; j += ystep, pin += ystep*in->nx)
        for (i = 0; i < in->nx; i += xstep)
            *pout++ = pin[i];

    return out;
}
