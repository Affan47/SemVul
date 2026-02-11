__repmgr_prepare_my_addr(env, dbt)
	ENV *env;
	DBT *dbt;
{
	DB_REP *db_rep;
	repmgr_netaddr_t addr;
	size_t size, hlen;
	u_int16_t port_buffer;
	u_int8_t *ptr;
	int ret;

	db_rep = env->rep_handle;
	LOCK_MUTEX(db_rep->mutex);
	addr = SITE_FROM_EID(db_rep->self_eid)->net_addr;
	UNLOCK_MUTEX(db_rep->mutex);


	port_buffer = htons(addr.port);
	size = sizeof(port_buffer) + (hlen = strlen(addr.host) + 1);
	if ((ret = __os_malloc(env, size, &ptr)) != 0)
		return (ret);

	DB_INIT_DBT(*dbt, ptr, size);

	memcpy(ptr, &port_buffer, sizeof(port_buffer));
	ptr = &ptr[sizeof(port_buffer)];
	memcpy(ptr, addr.host, hlen);

	return (0);
}
