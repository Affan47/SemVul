NYTP_read(NYTP_file ifile, void *buffer, size_t len, const char *what) {
    size_t got = NYTP_read_unchecked(ifile, buffer, len);
    if (got != len) {
        croak("Profile format error whilst reading %s at %ld%s: expected %ld got %ld, %s",
              what, NYTP_tell(ifile), NYTP_type_of_offset(ifile), (long)len, (long)got,
                (NYTP_eof(ifile)) ? "end of file" : NYTP_fstrerror(ifile));
    }
    return len;
}
