out_ca_port(ibnd_port_t * port, int group, char *out_prefix)
{
	char *str = NULL;
	char *rem_nodename = NULL;
	uint32_t iwidth = mad_get_field(port->info, 0,
					IB_PORT_LINK_WIDTH_ACTIVE_F);
	uint32_t ispeed = mad_get_field(port->info, 0,
					IB_PORT_LINK_SPEED_ACTIVE_F);
	uint32_t fdr10 = mad_get_field(port->ext_info, 0,
				       IB_MLNX_EXT_PORT_LINK_SPEED_ACTIVE_F);
	uint32_t cap_mask, espeed;

	fprintf(f, "%s[%d]", out_prefix ? out_prefix : "", port->portnum);
	if (port->node->type != IB_NODE_SWITCH)
		fprintf(f, "(%" PRIx64 ") ", port->guid);
	fprintf(f, "\t%s[%d]",
		node_name(port->remoteport->node), port->remoteport->portnum);
	str = out_ext_port(port->remoteport, group);
	if (str)
		fprintf(f, "%s", str);
	if (port->remoteport->node->type != IB_NODE_SWITCH)
		fprintf(f, " (%" PRIx64 ") ", port->remoteport->guid);

	rem_nodename = remap_node_name(node_name_map,
				       port->remoteport->node->guid,
				       port->remoteport->node->nodedesc);

	cap_mask = mad_get_field(port->info, 0, IB_PORT_CAPMASK_F);
	if (cap_mask & CL_NTOH32(IB_PORT_CAP_HAS_EXT_SPEEDS))
		espeed = mad_get_field(port->info, 0,
				       IB_PORT_LINK_SPEED_EXT_ACTIVE_F);
	else
		espeed = 0;

	fprintf(f, "\t\t# lid %d lmc %d \"%s\" lid %d %s%s",
		port->base_lid, port->lmc, rem_nodename,
		port->remoteport->node->type == IB_NODE_SWITCH ?
		port->remoteport->node->smalid :
		port->remoteport->base_lid,
		dump_linkwidth_compat(iwidth),
		(ispeed != 4 && !espeed) ?
			dump_linkspeed_compat(ispeed) :
			dump_linkspeedext_compat(espeed, ispeed, fdr10));

	if (full_info)
		fprintf(f, " s=%d w=%d", ispeed, iwidth);
	fprintf(f, "\n");

	free(rem_nodename);
}
