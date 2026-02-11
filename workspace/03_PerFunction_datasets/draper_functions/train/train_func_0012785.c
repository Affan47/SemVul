cpl_mask_extract(const cpl_mask * in,
                            cpl_size         llx,
                            cpl_size         lly,
                            cpl_size         urx,
                            cpl_size         ury)
{
    const cpl_size nx = urx - llx + 1;
    const cpl_size ny = ury - lly + 1;
    cpl_binary   * pout;


    cpl_ensure(in  != NULL,   CPL_ERROR_NULL_INPUT,    NULL);
    cpl_ensure(llx >  0,      CPL_ERROR_ILLEGAL_INPUT, NULL);
    cpl_ensure(llx <= urx,    CPL_ERROR_ILLEGAL_INPUT, NULL);
    cpl_ensure(urx <= in->nx, CPL_ERROR_ILLEGAL_INPUT, NULL);
    cpl_ensure(lly >  0,      CPL_ERROR_ILLEGAL_INPUT, NULL);
    cpl_ensure(lly <= ury,    CPL_ERROR_ILLEGAL_INPUT, NULL);
    cpl_ensure(ury <= in->ny, CPL_ERROR_ILLEGAL_INPUT, NULL);


    pout = (cpl_binary*)cpl_malloc((size_t)nx * (size_t)ny
                                   * sizeof(cpl_binary));

    if (nx == in->nx) {

        (void)memcpy(pout, in->data + (size_t)in->nx * (size_t)(lly - 1),
                     (size_t)nx * (size_t)ny * sizeof(cpl_binary));
    } else {
        const cpl_binary * pin = in->data + (llx - 1)
            + (size_t)in->nx * (size_t)(lly - 1);
        cpl_binary       * pj = pout;
        cpl_size           j;


        for (j = 0; j < ny; j++, pin += in->nx, pj += nx) {
            (void)memcpy(pj, pin, (size_t)nx);
        }
    }

    return cpl_mask_wrap(nx, ny, pout);
}
