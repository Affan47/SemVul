rb_io_ascii8bit_binmode(VALUE io)
{
    rb_io_t *fptr;

    GetOpenFile(io, fptr);
    if (fptr->readconv) {
        rb_econv_close(fptr->readconv);
        fptr->readconv = NULL;
    }
    if (fptr->writeconv) {
        rb_econv_close(fptr->writeconv);
        fptr->writeconv = NULL;
    }
    fptr->mode |= FMODE_BINMODE;
    fptr->mode &= ~FMODE_TEXTMODE;
    SET_BINARY_MODE_WITH_SEEK_CUR(fptr);

    fptr->encs.enc = rb_ascii8bit_encoding();
    fptr->encs.enc2 = NULL;
    fptr->encs.ecflags = 0;
    fptr->encs.ecopts = Qnil;
    clear_codeconv(fptr);

    return io;
}
