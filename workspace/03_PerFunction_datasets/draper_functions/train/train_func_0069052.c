eaptype_load(EAP_TYPES **type, int eap_type, CONF_SECTION *cs)
{
	char		buffer[64];
	char		namebuf[64];
	const char	*eaptype_name;
	lt_dlhandle	handle;
	EAP_TYPES	*node;

	eaptype_name = eaptype_type2name(eap_type, namebuf, sizeof(namebuf));
	snprintf(buffer, sizeof(buffer), "rlm_eap_%s", eaptype_name);


	handle = lt_dlopenext(buffer);
	if (handle == NULL) {
		radlog(L_ERR, "rlm_eap: Failed to link EAP-Type/%s: %s",
		       eaptype_name, lt_dlerror());
		return -1;
	}


	node = (EAP_TYPES *)malloc(sizeof(EAP_TYPES));
	if (node == NULL) {
		radlog(L_ERR, "rlm_eap: out of memory");
		return -1;
	}
	memset(node, 0, sizeof(*node));


	node->handle = handle;
	node->cs = cs;


	node->typename = eaptype_name;
	node->type_data = NULL;

	node->type = (EAP_TYPE *)lt_dlsym(node->handle, buffer);
	if (!node->type) {
		radlog(L_ERR, "rlm_eap: Failed linking to %s structure in %s: %s",
				buffer, eaptype_name, lt_dlerror());
		lt_dlclose(node->handle);
		free(node);
		return -1;
	}
	cf_log_module(cs, "Linked to sub-module %s", buffer);

	cf_log_module(cs, "Instantiating eap-%s", eaptype_name);

	if ((node->type->attach) &&
	    ((node->type->attach)(node->cs, &(node->type_data)) < 0)) {

		radlog(L_ERR, "rlm_eap: Failed to initialize type %s",
		       eaptype_name);
		lt_dlclose(node->handle);
		free(node);
		return -1;
	}

	*type = node;
	return 0;
}
