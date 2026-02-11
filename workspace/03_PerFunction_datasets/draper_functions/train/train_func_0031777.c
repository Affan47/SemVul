_slave_work(struct pinfo *pinfo)
{
    lms_t *lms = pinfo->common.lms;
    struct fds *fds = &pinfo->slave;
    int r, len, base;
    char path[PATH_SIZE];
    void **parser_match;
    struct db *db;
    unsigned int total_committed, counter;

    r = _db_and_parsers_setup(lms, &db, &parser_match);
    if (r < 0)
        return r;

    r = lms_db_update_id_get(db->handle);
    if (r < 0) {
        fprintf(stderr, "ERROR: could not get global update id.\n");
        goto done;
    }

    pinfo->common.update_id = r + 1;

    counter = 0;
    total_committed = 0;
    lms_db_begin_transaction(db->transaction_begin);

    while (((r = _slave_recv_path(fds, &len, &base, path)) == 0) && len > 0) {
        r = _db_and_parsers_process_file(
            lms, db, parser_match, path, len, base, pinfo->common.update_id);

        _slave_send_reply(fds, r);

        if (r < 0 ||
            (r == LMS_PROGRESS_STATUS_UP_TO_DATE ||
             r == LMS_PROGRESS_STATUS_SKIPPED))
            continue;

        counter++;
        if (counter > lms->commit_interval) {
            if (!total_committed) {
                total_committed += counter;
                lms_db_update_id_set(db->handle, pinfo->common.update_id);
            }

            lms_db_end_transaction(db->transaction_commit);
            lms_db_begin_transaction(db->transaction_begin);
            counter = 0;
        }
    }

    if (counter) {
        total_committed += counter;
        lms_db_update_id_set(db->handle, pinfo->common.update_id);
    }

    lms_db_end_transaction(db->transaction_commit);

done:
    free(parser_match);
    lms_parsers_finish(lms, db->handle);
    _db_close(db);

    return r;
}
