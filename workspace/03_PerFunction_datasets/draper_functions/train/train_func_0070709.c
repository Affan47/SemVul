setData(const QModelIndex& index, const QVariant& data,
                                int role)
{
	Q_UNUSED(role);

	if (!index.isValid())
		return false;


	if (index.column() == 0)
	{
		PgnDatabase* db = m_gameDatabaseManager->databases().at(index.row());
		db->setDisplayName(data.toString());
		m_gameDatabaseManager->setModified(true);

		return true;
	}
	return false;
}
