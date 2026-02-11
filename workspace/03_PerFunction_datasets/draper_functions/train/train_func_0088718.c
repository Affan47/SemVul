aim_ssi_addbuddy(aim_session_t *sess, const char *name,
	const char *group, const char *alias, const char *comment,
	const char *smsnum, int needauth)
{
	struct aim_ssi_item *parent;
	aim_tlvlist_t *data = NULL;

	if (!sess || !name || !group)
		return -EINVAL;


	if (!(parent = aim_ssi_itemlist_finditem(sess->ssi.local, group, NULL,
				AIM_SSI_TYPE_GROUP))) {

		if (!(parent = aim_ssi_itemlist_find(sess->ssi.local, 0x0000,
					0x0000)))
			if (!(parent = aim_ssi_itemlist_add(&sess->ssi.local,
						NULL, 0x0000, 0x0000,
						AIM_SSI_TYPE_GROUP, NULL)))
				return -ENOMEM;

		if (!(parent = aim_ssi_itemlist_add(&sess->ssi.local, group,
					0xFFFF, 0x0000, AIM_SSI_TYPE_GROUP,
					NULL)))
			return -ENOMEM;


		aim_ssi_itemlist_rebuildgroup(sess->ssi.local, NULL);
	}


	if (needauth)
		aim_addtlvtochain_noval(&data, 0x0066);
	if (alias)
		aim_addtlvtochain_raw(&data, 0x0131, strlen(alias), alias);
	if (smsnum)
		aim_addtlvtochain_raw(&data, 0x013a, strlen(smsnum), smsnum);
	if (comment)
		aim_addtlvtochain_raw(&data, 0x013c, strlen(comment), comment);


	aim_ssi_itemlist_add(&sess->ssi.local, name, parent->gid, 0xFFFF,
		AIM_SSI_TYPE_BUDDY, data);
	aim_freetlvchain(&data);


	aim_ssi_itemlist_rebuildgroup(sess->ssi.local, group);


	aim_ssi_sync(sess);

	return 0;
}
