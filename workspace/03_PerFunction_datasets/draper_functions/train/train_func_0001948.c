postLogMsg(EventsBuf *eb, EventTypeNum type, char *msg, va_list ap)
{
    char buf[BUF];
    nat size;

    size = vsnprintf(buf,BUF,msg,ap);
    if (size > BUF) {
        buf[BUF-1] = '\0';
        size = BUF;
    }

    if (!hasRoomForVariableEvent(eb, size)) {

        printAndClearEventBuf(eb);
    }

    postEventHeader(eb, type);
    postPayloadSize(eb, size);
    postBuf(eb,(StgWord8*)buf,size);
}
