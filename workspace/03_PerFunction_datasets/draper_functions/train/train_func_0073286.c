sa_free(struct sa *sa)
{
	if (sa->death) {
		timer_remove_event(sa->death);
		sa->death = 0;
		sa->refcnt--;
	}
	if (sa->soft_death) {
		timer_remove_event(sa->soft_death);
		sa->soft_death = 0;
		sa->refcnt--;
	}
	sa_remove(sa);
}
