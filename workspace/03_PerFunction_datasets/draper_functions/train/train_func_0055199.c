createProperties(QSqlDatabase & db) {
	QSqlQuery query = db.exec("CREATE TABLE properties (\n"
			"id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL ,\n"
			"name TEXT NOT NULL,\n"
			"value TEXT NOT NULL,\n"
			"show_in_label INTEGER NOT NULL,\n"
			"part_id INTEGER NOT NULL"
		")");
    debugError(query.isActive(), query);
    return query.isActive();
}
