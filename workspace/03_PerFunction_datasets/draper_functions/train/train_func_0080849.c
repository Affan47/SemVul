data(const QModelIndex &index, int role) const
{
	if (index.column() >= 4)
		return QVariant();

	QModelIndex sidx = mapToSource(index);
	KGpgNode *nd = m_model->nodeForIndex(sidx);

	if ((index.column() == 3) && (role == Qt::ToolTipRole))
		return nd->getId();

	if ((role != Qt::DisplayRole) && (index.column() <= 1))
		return m_model->data(sidx, role);

	if (role != Qt::DisplayRole)
		return QVariant();

	switch (index.column()) {
		case 0:	return nd->getName();
		case 1:	return nd->getEmail();
		case 2:	return Convert::toString(nd->getExpiration().date());
		case 3:	return nd->getId().right(8);
	}

	return QVariant();
}
