lb_tx_hash_to_port_mapping_get(struct team *team,
					  struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	struct team_port *port;
	unsigned char hash = ctx->info->array_index;

	port = LB_HTPM_PORT_BY_HASH(lb_priv, hash);
	ctx->data.u32_val = port ? port->dev->ifindex : 0;
	return 0;
}
