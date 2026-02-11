addPersonToDB(QHash<QString,QString> &aPerson) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO PERSON (xid_conference,id,name) VALUES (:xid_conference, :id, :name)");
    query.bindValue(":xid_conference", aPerson["conference_id"]);
    query.bindValue(":id", aPerson["id"]);
    query.bindValue(":name", aPerson["name"]);
    query.exec();


    query = QSqlQuery(db);
    query.prepare("INSERT INTO EVENT_PERSON (xid_conference,xid_event,xid_person) VALUES (:xid_conference, :xid_event, :xid_person)");
    query.bindValue(":xid_conference", aPerson["conference_id"]);
    query.bindValue(":xid_event", aPerson["event_id"]);
    query.bindValue(":xid_person", aPerson["id"]);
    query.exec();

}
