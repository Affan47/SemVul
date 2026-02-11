dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
	QString format = mimeTypes().first();
	if (!data || !data->hasFormat(format) || (action != Qt::MoveAction) || (column > 0) || parent.isValid()) {
		return false;
	}


	QByteArray bytes = data->data(format);
	QDataStream stream(&bytes, QIODevice::ReadOnly);
	QList<int> scenes;
	stream >> scenes;

	moveScenes(scenes, row);

	return true;
}
