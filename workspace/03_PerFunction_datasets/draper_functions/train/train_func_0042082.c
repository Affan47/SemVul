http_async_newstate(http_async_t *ha, http_state_t state)
{
	http_async_check(ha);

	ha->state = state;
	ha->last_update = tm_time();

	if (ha->state_chg != NULL)
		(*ha->state_chg)(ha, state);
}
