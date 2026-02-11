cpl_io_fits_close(const char * filename, int * status)
{
    if (*status == 0) {
        fitsfile * fptr;

        while ((fptr = cpl_io_fits_unset_fptr(filename, NULL))
               != NULL && !fits_close_file(fptr, status)) {
#ifdef _OPENMP
#pragma omp atomic
#endif
            cpl_nfitsfiles--;
#ifdef CPL_IO_FITS_DEBUG
            cpl_msg_debug(cpl_func, "Closed CFITSIO-file: %p (%s) (%d)",
                          (const void*)fptr, filename, (int)cpl_nfitsfiles);
#endif
        }
    }

    return *status;
}
