gf_odf_del_ipmp_tool_list(GF_IPMP_ToolList *ipmptl)
{
	if (!ipmptl) return GF_BAD_PARAM;

	while (gf_list_count(ipmptl->ipmp_tools)) {
		GF_IPMP_Tool *t = (GF_IPMP_Tool *) gf_list_get(ipmptl->ipmp_tools, 0);
		gf_list_rem(ipmptl->ipmp_tools, 0);
		if (t->tool_url) gf_free(t->tool_url);
		gf_free(t);
	}
	gf_list_del(ipmptl->ipmp_tools);
	gf_free(ipmptl);
	return GF_OK;
}
