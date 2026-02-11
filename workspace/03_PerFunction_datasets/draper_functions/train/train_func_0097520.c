werr(pam_handle_t *pamh, int sid, int ecode, char *phase)
{
    char buf[BUFSIZ];
    int len;

    sprintf(&buf[2], "pam %d no %s %s",
            sid, phase, pam_strerror(pamh, ecode));
    len = strlen(&buf[2]);
    put_int16(len, &buf[0]);
    if (write_fill(1, buf, len+2) != len+2)
        exit(1);
}
