_st_db_object_serialise(os_object_t o, char **buf, int *len) {
    char *key, *xml, *xmlstr;
    void *val;
    os_type_t ot;
    int cur = 0, xlen;

    log_debug(ZONE, "serialising object");

    *buf = NULL;
    *len = 0;

    if(os_object_iter_first(o))
        do {
            os_object_iter_get(o, &key, &val, &ot);

            log_debug(ZONE, "serialising key %s", key);

            ser_string_set(key, &cur, buf, len);
            ser_int_set(ot, &cur, buf, len);

            switch(ot) {
                case os_type_BOOLEAN:
                    ser_int_set(((int) (long) val) != 0, &cur, buf, len);
                    break;

                case os_type_INTEGER:
                    ser_int_set((int) (long) val, &cur, buf, len);
                    break;

                case os_type_STRING:
                    ser_string_set((char *) val, &cur, buf, len);
                    break;

                case os_type_NAD:
                    nad_print((nad_t) val, 0, &xml, &xlen);
                    xmlstr = (char *) malloc(sizeof(char) * (xlen + 1));
                    sprintf(xmlstr, "%.*s", xlen, xml);
                    ser_string_set(xmlstr, &cur, buf, len);
                    free(xmlstr);
                    break;

                case os_type_UNKNOWN:
                    break;
            }
        } while(os_object_iter_next(o));

    *len = cur;
}
