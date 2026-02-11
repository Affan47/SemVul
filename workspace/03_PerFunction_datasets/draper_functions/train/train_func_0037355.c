_mbstr_copy_pad(mpd_mbstr_t *dest, mpd_ssize_t n)
{
    dest->nbytes += n;
    dest->nchars += n;
    dest->cur -= n;

    if (dest->data != NULL) {
        char *cp = dest->data + dest->cur;
        while (--n >= 0) {
            cp[n] = '0';
        }
    }
}
