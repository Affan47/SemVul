find_uuid(QString uuid)
{
	if (model.rowCount() == 0)
		return NULL;

	QModelIndexList lst = model.match(model.index(0, 0), peer_role_uuid,
					  uuid);
	if (lst.size() == 0)
		return NULL;
	return model.itemFromIndex(lst[0]);
}
