extract_container(const Slapi_DN *entry_dn, const Slapi_DN *suffix_dn)
{
	char *result = NULL;

	if (slapi_sdn_scope_test(entry_dn,suffix_dn,LDAP_SCOPE_SUBTREE))
	{
		Slapi_DN parent;
		slapi_sdn_init(&parent);


		slapi_sdn_get_parent(entry_dn, &parent);

		while (0 != slapi_sdn_compare(&parent,suffix_dn))
		{
			Slapi_DN child;
			Slapi_RDN *rdn = slapi_rdn_new();
			char *rdn_type = NULL;
			char *rdn_str = NULL;

			slapi_sdn_get_rdn(&parent,rdn);
			slapi_rdn_get_first(rdn, &rdn_type, &rdn_str);
			if (rdn_str)
			{
				result = PR_sprintf_append(result, "%s=\"%s\",", rdn_type,rdn_str );
			}

			slapi_rdn_free(&rdn);

			slapi_sdn_init(&child);
			slapi_sdn_copy(&parent,&child);
			slapi_sdn_done(&parent);
			slapi_sdn_get_parent(&child, &parent);
			slapi_sdn_done(&child);
		}
		slapi_sdn_done(&parent);
	}

	if (NULL == result)
	{
		result = slapi_ch_strdup("");
	}
	return result;
}
