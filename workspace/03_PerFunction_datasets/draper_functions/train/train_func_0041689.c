replica_config_search (Slapi_PBlock *pb, Slapi_Entry* e, Slapi_Entry* entryAfter, int *returncode,
                       char *returntext, void *arg)
{
    multimaster_mtnode_extension *mtnode_ext;
    int changeCount = 0;
	PRBool reapActive = PR_FALSE;
    char val [64];


    PR_Lock (s_configLock);

	mtnode_ext = _replica_config_get_mtnode_ext (e);
	PR_ASSERT (mtnode_ext);

	if (mtnode_ext->replica) {
		Replica *replica;
		object_acquire (mtnode_ext->replica);
		if (cl5GetState () == CL5_STATE_OPEN) {
			changeCount = cl5GetOperationCount (mtnode_ext->replica);
		}
		replica = (Replica*)object_get_data (mtnode_ext->replica);
		if (replica) {
			reapActive = replica_get_tombstone_reap_active(replica);
		}


                if (search_requested_attr(pb, type_ruvElement)) {
                        replica_config_search_ruv(pb, e, replica);
                }


                if (search_requested_attr(pb, type_ruvElementUpdatetime)) {
                        replica_config_search_last_modified(pb, e, replica);
                }


		object_release (mtnode_ext->replica);
	}

    sprintf (val, "%d", changeCount);
    slapi_entry_add_string (e, type_replicaChangeCount, val);
	slapi_entry_attr_set_int(e, "nsds5replicaReapActive", (int)reapActive);

    PR_Unlock (s_configLock);

    return SLAPI_DSE_CALLBACK_OK;
}
