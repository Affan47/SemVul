sync_attrs_added(LDAPMod **original_mods, Slapi_Entry *local_entry) {
	int retval = 0;
	int ii = 0;
	char *useroc = "ntuser";
	char *groupoc = "ntgroup";
	size_t ulen = 6;
	size_t glen = 7;

	for (ii = 0; (retval == 0) && original_mods && original_mods[ii]; ++ii) {
		LDAPMod *mod = original_mods[ii];

		if (!(SLAPI_IS_MOD_ADD(mod->mod_op) || SLAPI_IS_MOD_REPLACE(mod->mod_op)) ||
			!mod->mod_type || !mod->mod_bvalues || !mod->mod_bvalues[0]) {
			continue;
		}

		if (!strcasecmp(mod->mod_type, "objectclass")) {
			int jj = 0;
			for (jj = 0; (retval == 0) && mod->mod_bvalues[jj]; ++jj) {
				struct berval *bv = mod->mod_bvalues[jj];
				if (((bv->bv_len == ulen) && !PL_strncasecmp(useroc, bv->bv_val, ulen)) ||
					((bv->bv_len == glen) && !PL_strncasecmp(groupoc, bv->bv_val, glen))) {
					retval = 1;
				}
			}
		}
	}


	if (retval == 1) {
		retval = add_remote_entry_allowed(local_entry);
		if (retval < 0) {
			retval = 0;
		}
	}

	return retval;
}
