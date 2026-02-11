display_entryrdn_self(DB *db, ID id, const char *nrdn, int indent)
{
    DBC *cursor = NULL;
    DBT key, data;
    char *keybuf = NULL;
    int rc = 0;
    rdn_elem *elem;
    char buffer[1024];

    rc = db->cursor(db, NULL, &cursor, 0);
    if (rc) {
        printf("Can't create db cursor: %s\n", db_strerror(rc));
        exit(1);
    }
    snprintf(buffer, sizeof(buffer), "%u:", id);
    keybuf = strdup(buffer);
    key.data = keybuf;
    key.size = key.ulen = strlen(keybuf) + 1;
    key.flags = DB_DBT_USERMEM;

    memset(&data, 0, sizeof(data));


    rc = cursor->c_get(cursor, &key, &data, DB_SET);
    if (rc) {
        fprintf(stderr, "Failed to position cursor at the key: %s: %s "
                            "(%d)\n", (char *)key.data, db_strerror(rc), rc);
        goto bail;
    }

    elem = (rdn_elem *)data.data;
    _entryrdn_dump_rdn_elem(keybuf, elem, indent);
    display_entryrdn_parent(db, id_stored_to_internal(elem->rdn_elem_id),
                            elem->rdn_elem_nrdn_rdn, indent);
    display_entryrdn_children(db, id_stored_to_internal(elem->rdn_elem_id),
                              elem->rdn_elem_nrdn_rdn, indent);
bail:
    free(keybuf);
    cursor->c_close(cursor);

    return;
}
