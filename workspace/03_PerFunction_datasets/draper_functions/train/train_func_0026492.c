insert_cert(sqlite3 *db,
                char* errorMsg,
                const char* serial,
                const char* subject,
                const char* issuer,
                const char* pkcs12)
{
    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare_v2(db, KCA_SQL_INSERT_CERT, strlen(KCA_SQL_INSERT_CERT), &stmt, NULL);
    if (SQLITE_OK == rc)
    {
        sqlite3_bind_text(stmt,1,serial,strlen(serial),NULL);
        sqlite3_bind_text(stmt,2,subject,strlen(subject),NULL);
        sqlite3_bind_text(stmt,3,issuer,strlen(issuer),NULL);
        sqlite3_bind_text(stmt,4,pkcs12,strlen(pkcs12),NULL);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    return rc;
}
