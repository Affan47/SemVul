insertProperty(const QString & name, const QString & value, qulonglong id, bool showInLabel) {
	QSqlQuery query;
	query.prepare("INSERT INTO properties(name, value, part_id, show_in_label) VALUES (:name, :value, :part_id, :show_in_label)");
	query.bindValue(":name", name.toLower().trimmed());
	query.bindValue(":value", value);
	query.bindValue(":part_id", id);
	query.bindValue(":show_in_label", showInLabel ? 1 : 0);
	if(!query.exec()) {
        debugExec("couldn't insert property", query);
		return false;
	} else {

	}

	return true;
}
