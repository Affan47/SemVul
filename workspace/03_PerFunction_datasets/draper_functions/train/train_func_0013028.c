netsnmp_inject_handler_into_subtree(netsnmp_subtree *tp, const char *name,
                                    netsnmp_mib_handler *handler,
                                    const char *before_what)
{
    netsnmp_subtree *tptr;
    netsnmp_mib_handler *mh;

    for (tptr = tp; tptr != NULL; tptr = tptr->next) {


        if (strcmp(tptr->label_a, name) == 0) {
            DEBUGMSGTL(("injectHandler", "injecting handler %s into %s\n",
                        handler->handler_name, tptr->label_a));
            netsnmp_inject_handler_before(tptr->reginfo, _clone_handler(handler),
                                          before_what);
        } else if (tptr->reginfo != NULL &&
		   tptr->reginfo->handlerName != NULL &&
                   strcmp(tptr->reginfo->handlerName, name) == 0) {
            DEBUGMSGTL(("injectHandler", "injecting handler into %s/%s\n",
                        tptr->label_a, tptr->reginfo->handlerName));
            netsnmp_inject_handler_before(tptr->reginfo, _clone_handler(handler),
                                          before_what);
        } else {
            for (mh = tptr->reginfo->handler; mh != NULL; mh = mh->next) {
                if (mh->handler_name && strcmp(mh->handler_name, name) == 0) {
                    DEBUGMSGTL(("injectHandler", "injecting handler into %s\n",
                                tptr->label_a));
                    netsnmp_inject_handler_before(tptr->reginfo,
                                                  _clone_handler(handler),
                                                  before_what);
                    break;
                } else {
                    DEBUGMSGTL(("injectHandler",
                                "not injecting handler into %s\n",
                                mh->handler_name));
                }
            }
        }
    }
}
