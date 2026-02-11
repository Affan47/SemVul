configure_view_sortlist(const cfg_obj_t *vconfig, const cfg_obj_t *config,
			cfg_aclconfctx_t *actx, isc_mem_t *mctx,
			dns_acl_t **aclp)
{
	isc_result_t result;
	const cfg_obj_t *maps[3];
	const cfg_obj_t *aclobj = NULL;
	int i = 0;

	if (*aclp != NULL)
		dns_acl_detach(aclp);
	if (vconfig != NULL)
		maps[i++] = cfg_tuple_get(vconfig, "options");
	if (config != NULL) {
		const cfg_obj_t *options = NULL;
		(void)cfg_map_get(config, "options", &options);
		if (options != NULL)
			maps[i++] = options;
	}
	maps[i] = NULL;

	(void)ns_config_get(maps, "sortlist", &aclobj);
	if (aclobj == NULL)
		return (ISC_R_SUCCESS);


	result = cfg_acl_fromconfig(aclobj, config, ns_g_lctx,
				    actx, mctx, 3, aclp);

	return (result);
}
