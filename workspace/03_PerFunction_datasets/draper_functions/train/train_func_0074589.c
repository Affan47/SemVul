aim_ssi_rename_group(aim_session_t *sess, const char *oldgn,
	const char *newgn)
{
	struct aim_ssi_item *group;

	if (!sess || !oldgn || !newgn)
		return -EINVAL;

	if (!(group = aim_ssi_itemlist_finditem(sess->ssi.local, oldgn, NULL,
				AIM_SSI_TYPE_GROUP)))
		return -EINVAL;

	free(group->name);
	group->name = (char *)malloc((strlen(newgn) + 1) * sizeof(char));
	strcpy(group->name, newgn);


	aim_ssi_sync(sess);

	return 0;
}
