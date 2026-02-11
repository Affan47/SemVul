_master_db_close(struct master_db *db)
{
    if (db->get_files)
        lms_db_finalize_stmt(db->get_files, "get_files");

    if (sqlite3_close(db->handle) != SQLITE_OK) {
        fprintf(stderr, "ERROR: clould not close DB (master): %s\n",
                sqlite3_errmsg(db->handle));
        return -1;
    }
    free(db);

    return 0;
}
