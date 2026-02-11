addScore(int secs, int count, int length) {

	QTreeWidgetItem* item = createScoreItem(secs, count, length);
	if (item == 0) {
		return;
	}
	m_scores->clearSelection();
	item->setSelected(true);


	QStringList scores;
	for (int i = 0; i < m_scores->topLevelItemCount(); ++i) {
		item = m_scores->topLevelItem(i);
		scores.append(item->data(1, Qt::UserRole).toString());
		scores.append(item->text(2));
		scores.append(item->text(3));
	}
	QSettings().setValue("Scores/Values", scores);

	show();
}
