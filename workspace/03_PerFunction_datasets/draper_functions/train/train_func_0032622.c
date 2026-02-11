MatchBan(const struct Channel *cptr, const char *ban)
{
	struct ChannelBan *tempban = NULL;

	tempban = cptr->firstban;
	while ((tempban != NULL) &&
	        (match(ban, tempban->mask) == 0))
		tempban = tempban->next;

	return (tempban);
}
