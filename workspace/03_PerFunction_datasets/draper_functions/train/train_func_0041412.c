data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	const PgnDatabase* db = m_gameDatabaseManager->databases().at(index.row());

	if (role == Qt::DisplayRole)
	{
		switch (index.column())
		{
			case 0:
				return db->displayName();

			default:
				return QVariant();
		}
	}
	else if (role == Qt::EditRole && index.column() == 0)
		return db->displayName();

	return QVariant();
}
