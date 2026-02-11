rc_addclass(struct rateclass **head, struct rateclass *inrc)
{
	struct rateclass *rc, *rc2;

	if (!(rc = malloc(sizeof(struct rateclass))))
		return;

	memcpy(rc, inrc, sizeof(struct rateclass));
	rc->next = NULL;

	for (rc2 = *head; rc2 && rc2->next; rc2 = rc2->next) ;

	if (!rc2)
		*head = rc;
	else
		rc2->next = rc;

	return;
}
