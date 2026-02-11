get(const PropertyReceiver* receiver) const
{
	const MultiColumnList* mcl = static_cast<const MultiColumnList*>(receiver);


	if (mcl->getColumnCount() > 0)
	{
	return PropertyHelper::uintToString(mcl->getColumnID(mcl->getSortColumn()));
}
	return "0";
}
