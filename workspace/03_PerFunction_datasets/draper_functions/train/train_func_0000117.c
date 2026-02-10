do_cram_md5 (int sock, const char *command, struct query *ctl, const char *strip)

{
    int result;
    int len;
    char buf1[1024];
    char msg_id[768];
    unsigned char response[16];
    char reply[1024];
    char *respdata;

    gen_send (sock, "%s CRAM-MD5", command);


    if ((result = gen_recv (sock, buf1, sizeof (buf1)))) {
	return result;
    }


    respdata = buf1;
    if (strip && strncmp(buf1, strip, strlen(strip)) == 0)
	respdata += strlen(strip);
    len = from64tobits (msg_id, respdata, sizeof(msg_id));

    if (len < 0) {
	report (stderr, GT_("could not decode BASE64 challenge\n"));
	return PS_AUTHFAIL;
    } else if ((size_t)len < sizeof (msg_id)) {
        msg_id[len] = 0;
    } else {
        msg_id[sizeof (msg_id)-1] = 0;
    }
    if (outlevel >= O_DEBUG) {
        report (stdout, GT_("decoded as %s\n"), msg_id);
    }


    hmac_md5((unsigned char *)ctl->password, strlen(ctl->password),
              (unsigned char *)msg_id, strlen (msg_id),
              response, sizeof (response));

    snprintf (reply, sizeof(reply),
              "%s %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
              ctl->remotename,
              response[0], response[1], response[2], response[3],
              response[4], response[5], response[6], response[7],
              response[8], response[9], response[10], response[11],
              response[12], response[13], response[14], response[15]);

    to64frombits (buf1, reply, strlen(reply));


    suppress_tags = TRUE;
    result = gen_transact(sock, "%s", buf1);
    suppress_tags = FALSE;
    if (result)
	return(result);
    else
	return(PS_SUCCESS);
}
