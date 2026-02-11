_slave_db_compile_all_stmts(struct slave_db *db)
{
    sqlite3 *handle;

    handle = db->handle;

    db->transaction_begin = lms_db_compile_stmt_begin_transaction(handle);
    if (!db->transaction_begin)
        return -1;

    db->transaction_commit = lms_db_compile_stmt_end_transaction(handle);
    if (!db->transaction_commit)
        return -2;

    db->delete_file_info = lms_db_compile_stmt_delete_file_info(handle);
    if (!db->delete_file_info)
        return -3;

    db->update_file_info = lms_db_compile_stmt_update_file_info(handle);
    if (!db->update_file_info)
        return -4;

    return 0;
}
