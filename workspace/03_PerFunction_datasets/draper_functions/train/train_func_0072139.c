blkid_parttable_get_id(blkid_parttable tab)
{
	return tab && *tab->id ? tab->id : NULL;
}
