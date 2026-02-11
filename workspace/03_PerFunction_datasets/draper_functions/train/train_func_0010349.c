store_file_load(void(*receive_msg)(Msg*))
{
    List *keys;
    Octstr *store_file, *key;
    Msg *msg;
    int retval, msgs;
    long end, pos;

    if (filename == NULL)
        return 0;

    mutex_lock(file_mutex);
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }

    store_file = octstr_read_file(octstr_get_cstr(filename));
    if (store_file != NULL)
        info(0, "Loading store file `%s'", octstr_get_cstr(filename));
    else {
        store_file = octstr_read_file(octstr_get_cstr(newfile));
        if (store_file != NULL)
            info(0, "Loading store file `%s'", octstr_get_cstr(newfile));
        else {
            store_file = octstr_read_file(octstr_get_cstr(bakfile));
            if (store_file != NULL)
        	       info(0, "Loading store file `%s'", octstr_get_cstr(bakfile));
            else {
                info(0, "Cannot open any store file, starting a new one");
                retval = open_file(filename);
                goto end;
            }
        }
    }

    info(0, "Store-file size %ld, starting to unpack%s", octstr_len(store_file),
        octstr_len(store_file) > 10000 ? " (may take awhile)" : "");


    pos = 0;
    msgs = 0;
    end = octstr_len(store_file);

    while (pos < end) {
        if (read_msg(&msg, store_file, &pos) == -1) {
            error(0, "Garbage at store-file, skipped.");
            continue;
        }
        if (msg_type(msg) == sms) {
            store_to_dict(msg);
            msgs++;
        } else if (msg_type(msg) == ack) {
            store_to_dict(msg);
        } else {
            warning(0, "Strange message in store-file, discarded, "
                "dump follows:");
            msg_dump(msg, 0);
        }
        msg_destroy(msg);
    }
    octstr_destroy(store_file);

    info(0, "Retrieved %d messages, non-acknowledged messages: %ld",
        msgs, dict_key_count(sms_dict));


    keys = dict_keys(sms_dict);
    while ((key = gwlist_extract_first(keys)) != NULL) {
        msg = dict_remove(sms_dict, key);
        if (store_to_dict(msg) != -1) {
            receive_msg(msg);
        } else {
            error(0, "Found unknown message type in store file.");
            msg_dump(msg, 0);
            msg_destroy(msg);
        }
        octstr_destroy(key);
    }
    gwlist_destroy(keys, octstr_destroy_item);


    retval = do_dump();

end:
    mutex_unlock(file_mutex);


    gwlist_remove_producer(loaded);


    if ((cleanup_thread = gwthread_create(store_dumper, NULL))==-1)
        panic(0, "Failed to create a cleanup thread!");

    return retval;
}
