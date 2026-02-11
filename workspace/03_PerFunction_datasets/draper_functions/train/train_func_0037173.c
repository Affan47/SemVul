IsChannelMember(const struct Channel *cptr, const struct Luser *lptr)
{
	struct ChannelUser *tempuser = NULL;

	if ((cptr == NULL) || (lptr == NULL))
		return 0;

	for (tempuser = cptr->firstuser; tempuser != NULL; tempuser =
	            tempuser->next)
	{
		if (tempuser->lptr == lptr)
			return 1;
	}

	return 0;
}
