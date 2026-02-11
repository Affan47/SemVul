_entryrdn_put_data(DBC *cursor, DBT *key, DBT *data, char type, DB_TXN *db_txn)
{
    int rc = -1;
    int db_retry = 0;

    slapi_log_error(SLAPI_LOG_TRACE, ENTRYRDN_TAG,
                                     "--> _entryrdn_put_data\n");
    if (NULL == cursor || NULL == key || NULL == data) {
        slapi_log_error(SLAPI_LOG_FATAL, ENTRYRDN_TAG,
                    "_entryrdn_put_data: Param error: Empty %s\n",
                    NULL==cursor?"cursor":NULL==key?"key":
                    NULL==data?"data":"unknown");
        goto bail;
    }

    for (db_retry = 0; db_retry < RETRY_TIMES; db_retry++) {
        rc = cursor->c_put(cursor, key, data, DB_NODUPDATA);
        if (rc) {
            if (DB_KEYEXIST == rc) {

                slapi_log_error(SLAPI_LOG_BACKLDBM, ENTRYRDN_TAG,
                                "_entryrdn_put_data: The same key (%s) and the "
                                "data exists in index\n",
                                (char *)key->data);
                break;
            } else {
                char *keyword = NULL;
                if (type == RDN_INDEX_CHILD) {
                    keyword = "child";
                } else if (type == RDN_INDEX_PARENT) {
                    keyword = "parent";
                } else {
                    keyword = "self";
                }
                slapi_log_error(ENTRYRDN_LOGLEVEL(rc), ENTRYRDN_TAG,
                                "_entryrdn_put_data: Adding the %s link (%s) "
                                "failed: %s (%d)\n", keyword, (char *)key->data,
                                dblayer_strerror(rc), rc);
                if ((DB_LOCK_DEADLOCK == rc) && !db_txn) {
                    ENTRYRDN_DELAY;
                    continue;
                }
                goto bail;
            }
        } else {
            break;
        }
    }
    if (RETRY_TIMES == db_retry) {
        slapi_log_error(SLAPI_LOG_FATAL, ENTRYRDN_TAG,
                        "_entryrdn_put_data: cursor put operation failed after [%d] retries\n",
                        db_retry);
        rc = DB_LOCK_DEADLOCK;
    }
bail:
    slapi_log_error(SLAPI_LOG_TRACE, ENTRYRDN_TAG, "<-- _entryrdn_put_data\n");
    return rc;
}
