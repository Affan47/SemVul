ois_extract_msg_from_buffer(char *str, SMSCenter *smsc)
{
    int len;
    int count;

    SAY2(8, "ois_extract_msg_from_buffer buflen=%ld", (long)smsc->buflen);

    str[0] = '\0';

    if (smsc->buflen < 7) {
	return 0;
    }

    if (strchr("SRDATECQLMPOVsrdatecqlmpov", smsc->buffer[0]) == NULL
	|| (smsc->buffer[1] & 0xf0) != 0x50) {

	goto error;
    }


    count = smsc->buffer[1] & 0x0f;
    for (len = 0; (size_t) len < smsc->buflen; ++len) {
	if (smsc->buffer[len] == EOL) {
	    if (--count < 0) {
		++len;
		break;
	    }
	}
    }

    if (count >= 0) {
	if (len < BUFLEN) {
	    return 0;
	}
	goto error;
    }


    memcpy(str, smsc->buffer, len);
    str[len] = '\0';
    smscenter_remove_from_buffer(smsc, len);

    return len;

 error:
    for (len = 0; (size_t) len < smsc->buflen && smsc->buffer[len] != EOL;
         ++len) ;
    if (len > BUFLEN) len = BUFLEN;

    memcpy(str, smsc->buffer, len);
    str[len] = '\0';
    smscenter_remove_from_buffer(smsc, smsc->buflen);

    return -len;
}
