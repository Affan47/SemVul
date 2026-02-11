xml_print_net_nfs_stats(struct activity *a, int curr, int tab,
					unsigned long long itv)
{
	struct stats_net_nfs
		*snnc = (struct stats_net_nfs *) a->buf[curr],
		*snnp = (struct stats_net_nfs *) a->buf[!curr];

	if (!IS_SELECTED(a->options) || (a->nr <= 0))
		goto close_xml_markup;

	xml_markup_network(tab, OPEN_XML_MARKUP);
	tab++;

	xprintf(tab, "<net-nfs "
		"call=\"%.2f\" "
		"retrans=\"%.2f\" "
		"read=\"%.2f\" "
		"write=\"%.2f\" "
		"access=\"%.2f\" "
		"getatt=\"%.2f\"/>",
		S_VALUE(snnp->nfs_rpccnt,     snnc->nfs_rpccnt,     itv),
		S_VALUE(snnp->nfs_rpcretrans, snnc->nfs_rpcretrans, itv),
		S_VALUE(snnp->nfs_readcnt,    snnc->nfs_readcnt,    itv),
		S_VALUE(snnp->nfs_writecnt,   snnc->nfs_writecnt,   itv),
		S_VALUE(snnp->nfs_accesscnt,  snnc->nfs_accesscnt,  itv),
		S_VALUE(snnp->nfs_getattcnt,  snnc->nfs_getattcnt,  itv));
	tab--;

close_xml_markup:
	if (CLOSE_MARKUP(a->options)) {
		xml_markup_network(tab, CLOSE_XML_MARKUP);
	}
}
