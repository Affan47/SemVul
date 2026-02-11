filter_unload(router_t r) {
    acl_t acl, tmp;

    acl = r->filter;

    while(acl != NULL) {
        tmp = acl->next;
        if(acl->from != NULL) free(acl->from);
        if(acl->to != NULL) free(acl->to);
        if(acl->what != NULL) free(acl->what);
        if(acl->redirect != NULL) free(acl->redirect);
        free(acl);
        acl = tmp;
    }
    r->filter = NULL;
}
