sa_hard_expire(void *v_sa)
{
	struct sa      *sa = v_sa;

	sa->death = 0;
	sa_release(sa);

	if ((sa->flags & (SA_FLAG_STAYALIVE | SA_FLAG_REPLACED)) ==
	    SA_FLAG_STAYALIVE)
		exchange_establish(sa->name, 0, 0);

	sa_delete(sa, 1);
}
