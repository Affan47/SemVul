_status_os_replace(storage_t st, const unsigned char *jid, char *status, char *show, time_t *lastlogin, time_t *lastlogout, nad_t nad) {
    os_t os = os_new();
    os_object_t o = os_object_new(os);
    os_object_put(o, "status", status, os_type_STRING);
    os_object_put(o, "show", show, os_type_STRING);
    os_object_put(o, "last-login", (void **) lastlogin, os_type_INTEGER);
    os_object_put(o, "last-logout", (void **) lastlogout, os_type_INTEGER);
    if(nad != NULL) os_object_put(o, "xml", nad, os_type_NAD);
    storage_replace(st, "status", jid, NULL, os);
    os_free(os);
}
