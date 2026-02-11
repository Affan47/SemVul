PerlIOAPR_seek(pTHX_ PerlIO *f, Off_t offset, int whence)
{
    PerlIOAPR *st = PerlIOSelf(f, PerlIOAPR);
    apr_seek_where_t where;
    apr_status_t rc;
    apr_off_t seek_offset = 0;

#ifdef MP_LARGE_FILES_CONFLICT
    if (offset != 0) {
        Perl_croak(aTHX_ "PerlIO::APR::seek with non-zero offset"
                   "is not supported with Perl built w/ -Duselargefiles"
                   " and APR w/o largefiles support");
    }
#else
    seek_offset = offset;
#endif


    if (PerlIO_flush(f) != 0) {
        return -1;
    }

    switch(whence) {
      case 0:
        where = APR_SET;
        break;
      case 1:
        where = APR_CUR;
        break;
      case 2:
        where = APR_END;
        break;
      default:
        Perl_croak(aTHX_ "unknown whence mode: %d", whence);
    }

    rc = apr_file_seek(st->file, where, &seek_offset);
    if (rc == APR_SUCCESS) {
        return 0;
    }

    return -1;
}
