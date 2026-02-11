qlink_cmp(const void *a, const void *b)
{
	const GList * const *l1 = a, * const *l2 = b;
	const pmsg_t *m1 = (*l1)->data, *m2 = (*l2)->data;

	if (pmsg_prio(m1) == pmsg_prio(m2))
		return gmsg_cmp(pmsg_start(m1), pmsg_start(m2), TRUE);
	else
		return pmsg_prio(m1) < pmsg_prio(m2) ? -1 : +1;
}
