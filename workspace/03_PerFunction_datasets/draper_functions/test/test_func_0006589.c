fetion_sip_get_msg_type(const gchar *sipmsg)
{
    gchar *res;
    gchar *pos;
    gint t;

    for (pos = (char*)sipmsg; *pos && *pos != ' '; pos ++);

    res = g_strndup(sipmsg, pos - sipmsg);

    if (strcmp(res, "I") == 0) {
        t = SIP_INVITATION;

    } else if (strcmp(res, "M") == 0) {
        t =  SIP_MESSAGE;

    } else if (strcmp(res, "BN") == 0) {
        t =  SIP_NOTIFICATION;

    } else if (strcmp(res, "SIP-C/4.0") == 0 ||
            strcmp(res , "SIP-C/1.0") == 0) {
        t = SIP_SIPC_4_0;

    } else if (strcmp(res, "IN") == 0) {
        t = SIP_INFO;

    } else if (strcmp(res, "O") == 0) {
        t =  SIP_OPTION;

    } else {
        t = SIP_UNKNOWN;
    }

    g_free(res);

    return t;
}
