__iscsi_match_session(node_rec_t *rec, char *targetname,
			  char *address, int port, struct iface_rec *iface,
			  unsigned sid)
{
	if (!rec) {
		log_debug(6, "no rec info to match\n");
		return 1;
	}

	log_debug(6, "match session [%s,%s,%d][%s %s,%s,%s]:%u",
		  rec->name, rec->conn[0].address, rec->conn[0].port,
		  rec->iface.name, rec->iface.transport_name,
		  rec->iface.hwaddress, rec->iface.ipaddress,
		  rec->session.sid);

	if (iface)
		log_debug(6, "to [%s,%s,%d][%s %s,%s,%s]:%u",
			  targetname, address, port, iface->name,
			  iface->transport_name, iface->hwaddress,
			  iface->ipaddress, sid);

	if (rec->session.sid && sid && rec->session.sid != sid)
		return 0;

	if (strlen(rec->name) && strcmp(rec->name, targetname))
		return 0;

	if (!iscsi_addr_match(rec->conn[0].address, address))
		return 0;

	if (rec->conn[0].port != -1 && port != rec->conn[0].port)
		return 0;

	if (!iface_match(&rec->iface, iface))
		return 0;

	return 1;
}
