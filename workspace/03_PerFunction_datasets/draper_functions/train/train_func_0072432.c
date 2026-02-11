http_subreq_error_ind(http_async_t *ha, http_errtype_t error, void *val)
{
	http_async_check(ha);
	g_assert(ha->parent != NULL);
	g_assert(ha->parent->error_ind);

	(*ha->parent->error_ind)(ha->parent, error, val);
}
