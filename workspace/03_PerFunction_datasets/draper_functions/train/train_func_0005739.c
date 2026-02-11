ip_acl(int tid, struct iscsi_connection *conn)
{
	int idx, err;
	char *addr;

	for (idx = 0;; idx++) {
		addr = acl_get(tid, idx);
		if (!addr)
			break;

		err = ip_match(conn, addr);
		if (!err)
			return 0;
	}
	return -EPERM;
}
