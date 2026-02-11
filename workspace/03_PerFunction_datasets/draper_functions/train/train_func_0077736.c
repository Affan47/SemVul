store_spool_init(const Octstr *store_dir)
{
    DIR *dir;

    store_messages = store_spool_messages;
    store_save = store_spool_save;
    store_save_ack = store_spool_save_ack;
    store_load = store_spool_load;
    store_dump = store_spool_dump;
    store_shutdown = store_spool_shutdown;
    store_status = store_spool_status;

    if (store_dir == NULL)
        return 0;


    if ((dir = opendir(octstr_get_cstr(store_dir))) == NULL) {
        error(errno, "Could not open directory `%s'", octstr_get_cstr(store_dir));
        return -1;
    }
    closedir(dir);

    loaded = gwlist_create();
    gwlist_add_producer(loaded);
    spool = octstr_duplicate(store_dir);
    counter = counter_create();

    return 0;
}
