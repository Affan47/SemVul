LocalExecuteInvalidationMessage(SharedInvalidationMessage *msg)
{
	int			i;

	if (msg->id >= 0)
	{
		if (msg->cc.dbId == MyDatabaseId || msg->cc.dbId == 0)
		{
			CatalogCacheIdInvalidate(msg->cc.id,
									 msg->cc.hashValue,
									 &msg->cc.tuplePtr);

			for (i = 0; i < syscache_callback_count; i++)
			{
				struct SYSCACHECALLBACK *ccitem = syscache_callback_list + i;

				if (ccitem->id == msg->cc.id)
					(*ccitem->function) (ccitem->arg,
										 msg->cc.id, &msg->cc.tuplePtr);
			}
		}
	}
	else if (msg->id == SHAREDINVALRELCACHE_ID)
	{
		if (msg->rc.dbId == MyDatabaseId || msg->rc.dbId == InvalidOid)
		{
			RelationCacheInvalidateEntry(msg->rc.relId);

			for (i = 0; i < relcache_callback_count; i++)
			{
				struct RELCACHECALLBACK *ccitem = relcache_callback_list + i;

				(*ccitem->function) (ccitem->arg, msg->rc.relId);
			}
		}
	}
	else if (msg->id == SHAREDINVALSMGR_ID)
	{


		smgrclosenode(msg->sm.rnode);
	}
	else
		elog(FATAL, "unrecognized SI message id: %d", msg->id);
}
