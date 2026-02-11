insertTag(const QString & tag, qulonglong id)
{
	QSqlQuery query;
	query.prepare("INSERT INTO tags(tag, part_id) VALUES (:tag, :part_id)");
	query.bindValue(":tag", tag.toLower().trimmed());
	query.bindValue(":part_id", id);
	if(!query.exec()) {
        debugExec("couldn't insert tag", query);
		m_swappingEnabled = false;
	} else {

	}

	return true;
}
