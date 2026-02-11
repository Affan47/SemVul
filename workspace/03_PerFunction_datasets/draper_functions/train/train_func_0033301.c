lldpctl_get_interfaces(lldpctl_conn_t *conn)
{
	struct lldpd_interface_list *ifs;
	void *p;
	int rc;

	RESET_ERROR(conn);

	rc = _lldpctl_do_something(conn,
	    CONN_STATE_GET_INTERFACES_SEND, CONN_STATE_GET_INTERFACES_RECV, NULL,
	    GET_INTERFACES,
	    NULL, NULL,
	    &p, &MARSHAL_INFO(lldpd_interface_list));
	if (rc == 0) {
		ifs = p;
		return _lldpctl_new_atom(conn, atom_interfaces_list, ifs);
	}
	return NULL;
}
