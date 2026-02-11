cpl_io_fits_find_fptr(cx_list_iterator  * pkey,
                                         const char        * filename,
                                         const int         * piomode,
                                         const struct stat * filestat)
{

    const int tid = omp_get_thread_num();
    const cpl_fitsfile_t * cpl_fitsfile = NULL;

    cpl_size i = 0;
    cx_list_iterator pos = cx_list_begin(cpl_fitslist);
    cpl_boolean found;

    while ((found = pos != cx_list_end(cpl_fitslist))) {

        cpl_fitsfile = (const cpl_fitsfile_t *)cx_list_get(cpl_fitslist, pos);

        if (filename == NULL) break;
        if ((piomode == NULL || *piomode == cpl_fitsfile->iomode) &&
            (((piomode == NULL || *piomode != READONLY)
              && cpl_fitsfile->writing) || cpl_fitsfile->tid == tid) &&
            (filestat != NULL && cpl_fitsfile->has_stat
             ? cpl_fitsfile->st_dev == filestat->st_dev &&
               cpl_fitsfile->st_ino == filestat->st_ino
             : !strcmp(cpl_fitsfile->name, filename))) break;

        pos = cx_list_next(cpl_fitslist, pos);
        i++;
    }

    if (found) {
        *pkey = pos;
#ifdef CPL_IO_FITS_DEBUG
        cpl_msg_debug(cpl_func, "File %s found (%d < %d): %p (I/O-mode: "
                      "%d) (tid: %d <=> %d)", filename, (int)i,
                      (int)cpl_nfitsfiles, (const void*)cpl_fitsfile->fptr,
                      cpl_fitsfile->iomode, tid, cpl_fitsfile->tid);
    } else if (piomode != NULL) {
        cpl_msg_debug(cpl_func, "File %s not found (%d) (I/O-mode: %d, "
                      "tid=%d)", filename, (int)cpl_nfitsfiles, *piomode, tid);
    } else {
        cpl_msg_debug(cpl_func, "File %s not found (%d) (tid=%d)", filename,
                      (int)cpl_nfitsfiles, tid);
#endif
    }

    return found;
}
