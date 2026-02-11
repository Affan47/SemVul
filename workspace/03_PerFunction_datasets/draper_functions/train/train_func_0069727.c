fileList(QStringList& list) const
{
	QListWidgetItem* item;
	int i = 0;

	while ((item = fileList_->item(i++)))
		list.append(item->text());
}
