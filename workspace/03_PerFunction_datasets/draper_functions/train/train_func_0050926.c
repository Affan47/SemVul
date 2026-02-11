ocon_state_end(const qpol_iterator_t * iter)
{
	ocon_state_t *os = NULL;

	if (iter == NULL || iter->state == NULL) {
		errno = EINVAL;
		return STATUS_ERR;
	}

	os = (ocon_state_t *) iter->state;

	if (os->cur == NULL)
		return 1;

	return 0;
}
