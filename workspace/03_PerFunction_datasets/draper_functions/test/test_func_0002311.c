admin_update_nbma(void *ctx, const char *cmd)
{
	char keyword[64];
	struct nhrp_peer_selector sel;
	struct update_nbma un;

	memset(&sel, 0, sizeof(sel));
	sel.type_mask = BIT(NHRP_PEER_TYPE_DYNAMIC_NHS);

	if (!parse_word(&cmd, sizeof(keyword), keyword))
		goto err;
	if (!nhrp_address_parse(keyword, &sel.next_hop_address, NULL))
		goto err;
	if (!parse_word(&cmd, sizeof(keyword), keyword))
		goto err;
	if (!nhrp_address_parse(keyword, &un.addr, NULL))
		goto err;

	un.count = 0;
	nhrp_peer_foreach(update_nbma, &un, &sel);

	admin_write(ctx,
		    "Status: ok\n"
		    "Entries-Affected: %d\n",
		    un.count);
	return;
err:
	admin_write(ctx,
		    "Status: failed\n"
		    "Reason: syntax-error\n"
		    "Near-Keyword: '%s'\n",
		    keyword);
	return;
}
