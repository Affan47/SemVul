replica_write_ruv (Replica *r)
{
	int rc = LDAP_SUCCESS;
	Slapi_Mod smod;
	Slapi_Mod smod_last_modified;
	LDAPMod *mods [3];
	Slapi_PBlock *pb;

	PR_ASSERT(r);

    PR_Lock(r->repl_lock);

    if (!r->repl_ruv_dirty)
    {
        PR_Unlock(r->repl_lock);
        return rc;
    }

	PR_ASSERT (r->repl_ruv);

	ruv_to_smod ((RUV*)object_get_data(r->repl_ruv), &smod);
	ruv_last_modified_to_smod ((RUV*)object_get_data(r->repl_ruv), &smod_last_modified);

    PR_Unlock (r->repl_lock);

	mods [0] = (LDAPMod *)slapi_mod_get_ldapmod_byref(&smod);
	mods [1] = (LDAPMod *)slapi_mod_get_ldapmod_byref(&smod_last_modified);
	mods [2] = NULL;
	pb = slapi_pblock_new();


	slapi_modify_internal_set_pb_ext(
		pb,
		r->repl_root,
		mods,
		NULL,
		RUV_STORAGE_ENTRY_UNIQUEID,
		repl_get_plugin_identity (PLUGIN_MULTIMASTER_REPLICATION),

        OP_FLAG_REPLICATED | OP_FLAG_REPL_FIXUP | OP_FLAG_TOMBSTONE_ENTRY |
		OP_FLAG_REPL_RUV );
	slapi_modify_internal_pb (pb);
	slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &rc);


    PR_Lock(r->repl_lock);

    if (rc == LDAP_SUCCESS)
    {
        r->repl_ruv_dirty = PR_FALSE;
    }
    else if (rc == LDAP_NO_SUCH_OBJECT)
    {


        rc = _replica_configure_ruv  (r, PR_TRUE);
        if (rc == 0)
            r->repl_ruv_dirty = PR_FALSE;
    }
	else
	{
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name,
			"replica_write_ruv: failed to update RUV tombstone for %s; "
			"LDAP error - %d\n",
			slapi_sdn_get_dn(r->repl_root), rc);
	}

    PR_Unlock(r->repl_lock);

	slapi_mod_done (&smod);
	slapi_mod_done (&smod_last_modified);
	slapi_pblock_destroy (pb);

	return rc;
}
