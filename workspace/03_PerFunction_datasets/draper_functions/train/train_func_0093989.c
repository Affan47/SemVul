flags(const QModelIndex &index) const
{
	if(!index.isValid())
		return Qt::ItemIsDropEnabled;

	Qt::ItemFlags back = Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled;

	switch(index.column())
	{
	case ColumnLabel:
		back |= Qt::ItemIsUserCheckable;
	case ColumnComment:
		back |= Qt::ItemIsEditable;
		break;
	case ColumnActionName:
		break;
	default:
		return Qt::NoItemFlags;
	}

	return back;
}
