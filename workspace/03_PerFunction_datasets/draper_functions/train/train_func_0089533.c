setAffiliationListEnabled(MUCItem::Affiliation a, bool b)
{
	QModelIndex index = affiliationListIndex(a);
	enabled_[(AffiliationListIndex) index.row()] = b;
	emit layoutChanged();
}
