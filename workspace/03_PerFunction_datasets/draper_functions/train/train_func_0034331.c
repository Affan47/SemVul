do_portcounters(Port * port, unsigned op, uint32_t unused,
			   uint8_t * data)
{
	Node *node = port->node;
	int portnum = mad_get_field(data, 0, IB_PC_PORT_SELECT_F);
	Portcounters totals;
	uint mask;
	Port *p;
	int i;

	if (node->type != SWITCH_NODE && portnum != port->portnum)
		return ERR_BAD_PARAM;

	if (node->type == SWITCH_NODE && portnum > node->numports
	    && portnum != 0xff)
		return ERR_BAD_PARAM;

	DEBUG("in node %" PRIx64 " port %" PRIx64 " portnum %d",
	      node->nodeguid, port->portguid, portnum);

	mask = mad_get_field(data, 0, IB_PC_COUNTER_SELECT_F);

	if (portnum != 0xff) {
		if (!(p = node_get_port(node, portnum)))
			return ERR_BAD_PARAM;

		if (op == IB_MAD_METHOD_SET)
			pc_reset(&p->portcounters, mask);

		pc_get(&p->portcounters, data);
		return 0;
	}

	memset(&totals, 0, sizeof totals);

	for (i = 0; i <= node->numports; i++) {

		if (!(p = node_get_port(node, i)))
			return ERR_BAD_PARAM;

		if (op == IB_MAD_METHOD_SET)
			pc_reset(&p->portcounters, mask);

		pc_sum(&totals, &p->portcounters);
	}

	pc_get(&totals, data);
	return 0;
}
