_st_db_free(st_driver_t drv) {
    drvdata_t data = (drvdata_t) drv->private;
    const char *key;
    int keylen;
    dbdata_t dbd;
    DB_ENV *env;
    union xhashv xhv;

    xhv.dbd_val = &dbd;
    if(xhash_iter_first(data->dbs))
        do {
            xhash_iter_get(data->dbs, &key, &keylen, xhv.val);

            log_debug(ZONE, "closing %.*s db", keylen, key);

            dbd->db->close(dbd->db, 0);
            free(dbd);
        } while(xhash_iter_next(data->dbs));

    xhash_free(data->dbs);

    xhash_free(data->filters);

    data->env->close(data->env, 0);


    if (db_env_create(&env, 0) == 0)
        env->remove(env, data->path, 0);

    free(data);
}
