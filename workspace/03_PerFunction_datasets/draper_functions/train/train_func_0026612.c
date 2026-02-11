parse_rawmessage_to_msg(SMSCenter *smsc, Msg **msg,
                                   char *rawmessage, int length)
{

    char emivars[128][1024];
    char *leftslash, *rightslash;
    char isotext[2048];
    int msgnbr;
    int tmpint;

    msgnbr = -1;

    memset(isotext, 0, sizeof(isotext));

    strncpy(isotext, rawmessage, length);
    leftslash = isotext;

    for (tmpint = 0; leftslash != NULL; tmpint++) {
        rightslash = strchr(leftslash + 1, '/');

        if (rightslash == NULL)
            rightslash = strchr(leftslash + 1, '\3');

        if (rightslash == NULL)
            break;

        *rightslash = '\0';
        strcpy(emivars[tmpint], leftslash + 1);
        leftslash = rightslash;
    }

    if (strcmp(emivars[3], "01") == 0) {
        if (strcmp(emivars[7], "2") == 0) {
            strcpy(isotext, emivars[8]);
        } else if (strcmp(emivars[7], "3") == 0) {
            parse_emi_to_iso88591(emivars[8], isotext, sizeof(isotext),
                                  smsc->alt_charset);
        } else {
            error(0, "Unknown 01-type EMI SMS (%s)", emivars[7]);
            strcpy(isotext, "");
        }
    } else if (strcmp(emivars[3], "51") == 0) {
        parse_emi_to_iso88591(emivars[24], isotext, sizeof(isotext),
                              smsc->alt_charset);
    } else if (strcmp(emivars[3], "52") == 0) {
        parse_emi_to_iso88591(emivars[24], isotext, sizeof(isotext),
                              smsc->alt_charset);
    } else {
        error(0, "HEY WE SHOULD NOT BE HERE!! Type = %s", emivars[3]);
        strcpy(isotext, "");
    }

    *msg = msg_create(sms);
    if (*msg == NULL) goto error;

    (*msg)->sms.sender = octstr_create(emivars[5]);
    (*msg)->sms.receiver = octstr_create(emivars[4]);
    (*msg)->sms.msgdata = octstr_create(isotext);
    (*msg)->sms.udhdata = NULL;

    return msgnbr;

error:
    return -1;
}
