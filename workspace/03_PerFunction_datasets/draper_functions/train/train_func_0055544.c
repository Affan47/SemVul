_cl5WriteMod (LDAPMod *mod, char **buff)
{
	char *orig_pos;
	char *pos;
	PRInt32 count;
	struct berval *bv;
	struct berval *encbv;
	struct berval *bv_to_use;
	Slapi_Mod smod;
	int rc = -1;

	if (NULL == mod) {
		return rc;
	}
	if (SLAPD_UNHASHED_PW_NOLOG == slapi_config_get_unhashed_pw_switch()) {
		if (0 == strcasecmp(mod->mod_type, PSEUDO_ATTR_UNHASHEDUSERPASSWORD)) {

			return rc;
		}
	}

	slapi_mod_init_byref(&smod, mod);

	orig_pos = pos = *buff;

	*pos = (PRUint8)slapi_mod_get_operation (&smod);
	pos ++;

	_cl5WriteString (slapi_mod_get_type (&smod), &pos);


	count = PR_htonl(slapi_mod_get_num_values(&smod));
	memcpy (pos, &count, sizeof (count));
	pos += sizeof (PRInt32);


	rc = 0;

	bv = slapi_mod_get_first_value (&smod);
	while (bv)
	{
		encbv = NULL;
		rc = clcrypt_encrypt_value(s_cl5Desc.clcrypt_handle,
		                           bv, &encbv);
		if (rc > 0) {

			bv_to_use = bv;
		} else if ((0 == rc) && encbv) {

			bv_to_use = encbv;
		} else {
			slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
						"_cl5WriteMod: encrypting \"%s: %s\" failed\n",
						slapi_mod_get_type(&smod), bv->bv_val);
			bv_to_use = NULL;
			rc = -1;
			break;
		}
		if (bv_to_use) {
			_cl5WriteBerval (bv_to_use, &pos);
		}
		slapi_ch_bvfree(&encbv);
		bv = slapi_mod_get_next_value (&smod);
	}

	if (rc < 0) {
		(*buff) = orig_pos;
	} else {
		(*buff) = pos;
	}

	slapi_mod_done (&smod);
	return rc;
}
