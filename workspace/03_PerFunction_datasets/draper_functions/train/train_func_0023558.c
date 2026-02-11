mutex_is_owned_by(const mutex_t *m, const thread_t t)
{
	mutex_check(m);

	return mutex_is_owned_by_fast(m, t);
}
