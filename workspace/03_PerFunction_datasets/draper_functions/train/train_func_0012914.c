procmsg_msg_has_flagged_parent(MsgInfo *info, MsgPermFlags perm_flags)
{
	gboolean result;
	static GHashTable *parentmsgs = NULL;

	if (parentmsgs == NULL)
		parentmsgs = g_hash_table_new(NULL, NULL);

	result = procmsg_msg_has_flagged_parent_real(info, perm_flags, parentmsgs);
	g_hash_table_foreach_remove(parentmsgs, parentmsgs_hash_remove, NULL);

	return result;
}
