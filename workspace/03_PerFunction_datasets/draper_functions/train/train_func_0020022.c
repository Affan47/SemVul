capture_chars(struct current *current, int pos, int n)
{
    if (pos >= 0 && (pos + n - 1) < current->chars) {
        int p1 = utf8_index(current->buf, pos);
        int nbytes = utf8_index(current->buf + p1, n);

        if (nbytes) {
            free(current->capture);

            current->capture = (char *)malloc(nbytes + 1);
            memcpy(current->capture, current->buf + p1, nbytes);
            current->capture[nbytes] = '\0';
        }
    }
}
