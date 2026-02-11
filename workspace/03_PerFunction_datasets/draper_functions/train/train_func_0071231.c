processXmlListMenu2(int tvisits, char* p)
{
    boolean_t wait = BOOL_NO;

    p += strlen(XML_LIST_MENU2);

    INFO2("[WS]: (%d) Got list menu item %s", tvisits, p);

    char * item = strstr(p,",");
    if (!item) {
        INFO2("[WS]: (%d) Improper item in list, ignore", tvisits);
    } else {

        (*item) = '\0';
        item++;

        int lidx = atoi(p);
        int midx = atoi(item) - 1;

        if (handleMenuOnList(midx, lidx, tvisits)) {
            wait = BOOL_YES;
        }
    }
    return wait;
}
