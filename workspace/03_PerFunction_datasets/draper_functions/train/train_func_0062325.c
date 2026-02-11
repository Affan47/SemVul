cpl_is_fits(const char * self)
{
    int          error = 0;
    int          is_fits = 1;
    fitsfile   * fptr;


    cpl_ensure(self != NULL, CPL_ERROR_NULL_INPUT, -1);

    if (cpl_io_fits_open_diskfile(&fptr, self, READONLY, &error)) {
        is_fits = error == FILE_NOT_OPENED ? -2 : 0;

        if (is_fits < 0)
            (void)cpl_error_set_fits(CPL_ERROR_FILE_NOT_FOUND, error,
                                     fits_open_diskfile, "filename='%s'", self);
        error = 0;
#ifndef CPL_IO_FITS_REWIND
    } else if (fits_movabs_hdu(fptr, 1, NULL, &error)) {


        is_fits = error == FILE_NOT_OPENED ? -2 : 0;

        if (is_fits < 0)
            (void)cpl_error_set_fits(CPL_ERROR_FILE_NOT_FOUND, error,
                                     fits_movabs_hdu, "filename='%s'", self);
        error = 0;
#endif
    } else if (fits_read_imghdr(fptr, 0,  NULL, NULL, NULL, NULL, NULL, NULL,
                                NULL, &error)) {
        is_fits = error == FILE_NOT_OPENED ? -2 : 0;

        if (is_fits < 0)
            (void)cpl_error_set_fits(CPL_ERROR_FILE_NOT_FOUND, error,
                                     fits_read_imghdr, "filename='%s'", self);
        error = 0;
    }

    if (fptr != NULL && cpl_io_fits_close_file(fptr, &error) != 0) {

        is_fits = -1;
        (void)cpl_error_set_fits(CPL_ERROR_BAD_FILE_FORMAT, error,
                                 fits_close_file, "filename='%s'", self);
    }

    return is_fits;
}
