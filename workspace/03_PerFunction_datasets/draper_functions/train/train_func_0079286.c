channel_remove (CHANNEL * chan, USER * user)
{
    LIST **list, *tmpList;
    CHANUSER *chanUser;

    for (list = &chan->users; *list; list = &(*list)->next)
    {
	chanUser = (*list)->data;
	ASSERT (chanUser->magic == MAGIC_CHANUSER);
	if (chanUser->user == user)
	{
	    tmpList = *list;
	    *list = (*list)->next;
	    FREE (tmpList);
	    FREE (chanUser);
	    break;
	}
    }
    return chan->users;
}
