deleteConference(int id) {
    QSqlQuery query(db);
    bool success = query.exec("BEGIN IMMEDIATE TRANSACTION");
    emitSqlQueryError(query);

    QStringList sqlList;
    sqlList << "DELETE FROM LINK WHERE xid_conference = ?"
            << "DELETE FROM EVENT_ROOM WHERE xid_conference = ?"
            << "DELETE FROM EVENT_PERSON WHERE xid_conference = ?"
            << "DELETE FROM EVENT WHERE xid_conference = ?"
            << "DELETE FROM ROOM WHERE xid_conference = ?"
            << "DELETE FROM PERSON WHERE xid_conference = ?"
            << "DELETE FROM TRACK WHERE xid_conference = ?"
            << "DELETE FROM CONFERENCE WHERE id = ?";

    foreach (const QString& sql, sqlList) {
        query.prepare(sql);
        query.bindValue(0, id);
        success &= query.exec();
        emitSqlQueryError(query);
    }

    success &= query.exec("COMMIT");
    emitSqlQueryError(query);

    return success;
}
