checkWebPort(char* buf, int capacity)
{


    if (queueExists(Q_WEB) != RC_OK) {
        return 0;
    }


    int l = 0;


    wMessage* wm = (wMessage*) queuePop(Q_WEB);
    if (wm != NULL) {
        logger(L_DBG, "[DS]: Got event");

        if (wm->button > 0) {
            INFO2("[DS]: Button pressed %d", wm->button);
            char bbuf[16];
            if (wm->button == 10) {
                sprintf(bbuf,"Msg:%c",'*');
            } else if (wm->button == 11) {
                sprintf(bbuf,"Msg:%c",'0');
            } else if (wm->button == 12) {
                sprintf(bbuf,"Msg:%c",'#');
            } else {
                sprintf(bbuf,"Msg:%d",wm->button);
            }
            strncpy(buf,bbuf,capacity);
            l = strlen(buf);
        } else if (wm->string) {
            INFO2("[DS]: Data %s", wm->string->str);

            strncpy(buf,wm->string->str,capacity);
            l = strlen(wm->string->str);
        }
        freeWMessage(wm);
    }
    return l;
}
