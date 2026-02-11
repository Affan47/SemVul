krb5_rc_io_close(krb5_context context, krb5_rc_iostuff *d)
{
    if (d->fn != NULL) {
        free(d->fn);
        d->fn = NULL;
    }
    if (d->fd != -1) {
        if (close(d->fd) == -1)
            return KRB5_RC_IO_UNKNOWN;
        d->fd = -1;
    }
    return 0;
}
