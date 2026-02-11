platram_setrw(struct platram_info *info, int to)
{
	if (info->pdata == NULL)
		return;

	if (info->pdata->set_rw != NULL)
		(info->pdata->set_rw)(info->dev, to);
}
