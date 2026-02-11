_ar_pipe_get_password(authreg_t ar, char *username, char *realm, char password[257])
{
    moddata_t data = (moddata_t) ar->private;
    char buf[1024];

    if(_ar_pipe_write(ar, data->out, "GET-PASSWORD %s %s\n", username, realm) < 0)
        return 1;

    if(_ar_pipe_read(ar, data->in, buf, 1023) <= 0)
        return 1;

    if(buf[0] != 'O' || buf[1] != 'K')
        return 1;

    if(buf[2] != ' ' || buf[3] == '\0')
    {
        log_debug(ZONE, "malformed response from pipe");
        return 1;
    }

    if(apr_base64_decode_len(&buf[3], strlen(&buf[3])) >= 256) {
        log_debug(ZONE, "decoded password longer than buffer");
        return 1;
    }

    apr_base64_decode(password, &buf[3], strlen(&buf[3]));

    log_debug(ZONE, "got password: %s", password);

    return 0;
}
