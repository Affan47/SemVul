cpl_mask_collapse_create(const cpl_mask  *   in,
                                    int                 dir)
{
    cpl_mask         * out;
    const cpl_binary * pin;
    cpl_size           j;


    cpl_ensure(in != NULL, CPL_ERROR_NULL_INPUT, NULL);


    pin = in->data;


    if (dir == 0) {
        cpl_binary   * pout = (cpl_binary*)cpl_malloc((size_t)in->nx
                                                      * sizeof(cpl_binary));

        const cpl_size nword = in->nx / (cpl_size)sizeof(size_t);


        cpl_size ifirst   = 0;
        cpl_size ilast    = nword-1;

        cpl_size * pfirst = &ifirst;
        cpl_size * plast  = &ilast;


        size_t     * word1 = (size_t*)memcpy(pout, pin, (size_t)in->nx);
        pin += in->nx;


        for (j = 1; j < in->ny; j++, pin += in->nx) {
            const size_t * word2  = (const size_t*)pin;
            unsigned       donext = 0;
            const cpl_size klast = ilast;
            cpl_size       i;

            for (i = ifirst; i < 1 + klast; i++) {


                if ((word1[i] &= word2[i])) *(donext++ ? plast : pfirst) = i;
            }


            for (i = nword * (cpl_size)sizeof(size_t); i < in->nx; i++) {
                if ((pout[i] &= pin[i])) donext = 1;
            }
            if (!donext) break;
        }

        out = cpl_mask_wrap(in->nx, 1, pout);

    } else if (dir == 1) {


        cpl_binary * pout = (cpl_binary*)cpl_malloc((size_t)in->ny
                                                    * sizeof(cpl_binary));


        for (j = 0; j < in->ny; j++) {


            const cpl_binary * pfind = pin + (size_t)in->nx * (size_t)j;

            const size_t szfind = (size_t)in->nx * (size_t)(in->ny - j);


            const cpl_binary * pnext = memchr(pfind, CPL_BINARY_0, szfind);


            const cpl_size row0 = pnext != NULL
                ? (cpl_size)((size_t)pnext-(size_t)pin) / in->nx : in->ny;

            for (; j < row0; j++) {
                pout[j] = CPL_BINARY_1;
            }


            if (pnext != NULL) pout[j] = CPL_BINARY_0;
        }

        out = cpl_mask_wrap(1, in->ny, pout);

    } else {
        out = NULL;
        (void)cpl_error_set_(CPL_ERROR_ILLEGAL_INPUT);
    }


    return out;
}
