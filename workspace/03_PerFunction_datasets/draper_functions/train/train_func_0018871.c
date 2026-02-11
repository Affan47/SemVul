list_connections(FILE * out)
{
	int i;

	for (i = 0; i < IBSIM_MAX_CLIENTS; i++) {
		if (!clients[i].pid)
			continue;
		fprintf(out,
			"Client %d: pid %d connected at \"%s\" port 0x%" PRIx64
			", lid %d, qp %d %s\n", i, clients[i].pid,
			clients[i].port->node->nodeid,
			clients[i].port->portguid, clients[i].port->lid,
			clients[i].qp, clients[i].issm ? "SM" : "");
	}
	return 0;
}
