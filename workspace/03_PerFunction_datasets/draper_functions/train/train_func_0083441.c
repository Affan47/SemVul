dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int, const QModelIndex &parent)
{
	if (!data || action != Qt::MoveAction || !(data->hasFormat("application/vnd.text.list") || data->hasFormat("text/plain")))
		return false;


	QStringList newItems;
	int nb_rows = 0;
	if (data->hasFormat("application/vnd.text.list")) {
		QByteArray encodedData = data->data("application/vnd.text.list");
		QDataStream stream(&encodedData, QIODevice::ReadOnly);
		while (!stream.atEnd()) {
			QString text;
			stream >> text;
			newItems << text;
			nb_rows++;
		}
	}
	else if (data->hasFormat("text/plain")) {
		QString item(data->data("text/plain"));
		if (Jid(item).isValid()) {
			newItems += item;
			nb_rows++;
		}
	}

	if (nb_rows == 0)
		return false;


	QModelIndex real_index;
	if (parent.isValid())  {
		real_index = (parent.parent().isValid() ? parent.parent() : parent);
	}
	else {
		if (row > 0)
			real_index = index(row-1,0,parent);
		else if (row == 0)
			real_index = index(0,0,parent);
		else
			real_index = index(Outcast,0,parent);
	}
	int real_row = rowCount(real_index);


	insertRows(real_row, nb_rows, real_index);
	foreach (QString text, newItems) {
		QModelIndex idx = index(real_row, 0, real_index);
		setData(idx, text);
		real_row++;
	}

	return true;
}
