_ar_db_delete_user(authreg_t ar, char *username, char *realm)
{
    DB *db;
    DBT key;
    int err;

    if(_ar_db_fetch_user(ar, username, realm) == NULL)
        return 1;

    db = _ar_db_get_realm_db(ar, realm);
    if(db == NULL)
        return 1;

    memset(&key, 0, sizeof(DBT));

    key.data = username;
    key.size = strlen(username);

    err = db->del(db, NULL, &key, 0);
    if(err != 0)
        log_write(ar->c2s->log, LOG_ERR, "db: couldn't delete auth creds for user '%s' (realm '%s'): %s", username, realm, db_strerror(err));

    return err;
}
