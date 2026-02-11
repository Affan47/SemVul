search_log_unknown_ggep(const gnutella_node_t *n,
	const gnet_results_set_t *rs,
	const extvec_t *e, const char *vendor)
{
	if (GNET_PROPERTY(search_debug) <= 3 && GNET_PROPERTY(ggep_debug) <= 3)
		return;


	if ((T_LIME == rs->vcode.u32 || rs->hops > 0) && is_lime_return_path(e))
		return;

	search_log_ggep(n, e, vendor, "unknown");
}
