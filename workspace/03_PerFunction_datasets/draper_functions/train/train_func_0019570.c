processXmlShortMenu(int tvisits, char* p)
{
    boolean_t wait = BOOL_NO;

    p += strlen(XML_SHORT_MENU);

    INFO2("[WS]: (%d) Got menu item %s", tvisits, p);

    int idx = atoi(p) - 1;
    mutexLock(M_STATE);
    int iLen = menuSize();
    mutexUnlock(M_STATE);

    if (idx >= 0 && idx < iLen) {
        mutexLock(M_STATE);

        SingleList *menuItem = menuNth(idx);
        if (menuItem) {

            wMessage* wm = (wMessage*) malloc(sizeof(wMessage));
            wm->button = -1;
            wm->string = stringNew("");
            stringAppend(wm->string, ((string_t*) menuItem->data)->str);

            sendToWebServer(wm);
            wait = BOOL_YES;
        } else {
            ERROR2("[WS]: Can not get list item #%d from list having %d items", idx, iLen);
        }
        mutexUnlock(M_STATE);
    } else {
        INFO2("[WS]: (%d) Wrong selected index in list, ignore..", tvisits);
    }

    return wait;
}
