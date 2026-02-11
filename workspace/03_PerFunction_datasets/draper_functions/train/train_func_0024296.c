__repmgr_add_dbt(v, dbt)
	REPMGR_IOVECS *v;
	const DBT *dbt;
{
	if (dbt->size > 0) {
		v->vectors[v->count].iov_base = dbt->data;
		v->vectors[v->count++].iov_len = dbt->size;
		v->total_bytes += dbt->size;
	}
}
