send_reply(struct sockaddr_storage sfrom, socklen_t sfromsiz,
	   int status, const char *user, const char *mbox,
	   int numrecent, time_t lastread, time_t lastarrived)
{
    char buf[MAX_MAILBOX_PATH + 16 + 9];
    int siz;

    switch(status) {
        case REQ_DENY:
            sendto(soc,"PERMDENY",9,0,(struct sockaddr *) &sfrom, sfromsiz);
            break;
        case REQ_OK:
            siz = snprintf(buf, sizeof(buf), "%s|%s|%d|%u|%u",
			   user, mbox, numrecent,
			   (uint32_t)lastread, (uint32_t)lastarrived);
            sendto(soc,buf,siz,0,(struct sockaddr *) &sfrom, sfromsiz);
            break;
        case REQ_UNK:
            sendto(soc,"UNKNOWN",8,0,(struct sockaddr *) &sfrom, sfromsiz);
            break;
    }
}
