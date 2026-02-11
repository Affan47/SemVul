multimaster_preop_add (Slapi_PBlock *pb)
{
    Slapi_Operation *op;
    int is_replicated_operation;
    int is_fixup_operation;
    int is_legacy_operation;

    slapi_pblock_get(pb, SLAPI_OPERATION, &op);


    is_legacy_operation =
        operation_is_flag_set(op,OP_FLAG_LEGACY_REPLICATION_DN);
    if (is_legacy_operation)
    {
        copy_operation_parameters(pb);
        slapi_operation_set_csngen_handler(op,
                                           (void*)replica_generate_next_csn);
        return SLAPI_PLUGIN_SUCCESS;
    }

    if (!is_mmr_replica (pb))
    {
        copy_operation_parameters(pb);
        return SLAPI_PLUGIN_SUCCESS;
    }

    is_replicated_operation= operation_is_flag_set(op,OP_FLAG_REPLICATED);
    is_fixup_operation= operation_is_flag_set(op,OP_FLAG_REPL_FIXUP);

    if(is_replicated_operation)
    {
        if(!is_fixup_operation)
        {
            LDAPControl **ctrlp;
            char sessionid[REPL_SESSION_ID_SIZE];
               get_repl_session_id (pb, sessionid, NULL);
            slapi_pblock_get(pb, SLAPI_REQCONTROLS, &ctrlp);
            if (NULL != ctrlp)
            {
                CSN *csn = NULL;
                char *target_uuid = NULL;
                char *superior_uuid= NULL;
                int drc = decode_NSDS50ReplUpdateInfoControl(ctrlp, &target_uuid, &superior_uuid, &csn, NULL );
                if (-1 == drc)
                {
                    slapi_log_error(SLAPI_LOG_FATAL, REPLICATION_SUBSYSTEM,
                            "%s An error occurred while decoding the replication update "
                            "control - Add\n", sessionid);
                }
                else if (1 == drc)
                {


                    struct slapi_operation_parameters *op_params;


                    if (!process_operation (pb, csn))
                    {
                        slapi_send_ldap_result(pb, LDAP_SUCCESS, 0,
                            "replication operation not processed, replica unavailable "
                            "or csn ignored", 0, 0);
                        csn_free (&csn);
                        slapi_ch_free ((void**)&target_uuid);
                        slapi_ch_free ((void**)&superior_uuid);

                        return SLAPI_PLUGIN_FAILURE;
                    }

                    operation_set_csn(op, csn);
                    slapi_pblock_set( pb, SLAPI_TARGET_UNIQUEID, target_uuid);
                    slapi_pblock_get( pb, SLAPI_OPERATION_PARAMETERS, &op_params );

                    op_params->p.p_add.parentuniqueid= superior_uuid;

                    if(target_uuid!=NULL)
                    {


                        Slapi_Entry    *addentry;
                        char *entry_uuid;
                        slapi_pblock_get( pb, SLAPI_ADD_ENTRY, &addentry );
                        entry_uuid= slapi_entry_attr_get_charptr( addentry, SLAPI_ATTR_UNIQUEID);
                        if(entry_uuid==NULL)
                        {

                            slapi_entry_set_uniqueid(addentry, slapi_ch_strdup(target_uuid));
                        }
                        else
                        {
                            if(strcasecmp(entry_uuid,target_uuid)!=0)
                            {
                                slapi_log_error(SLAPI_LOG_FATAL, REPLICATION_SUBSYSTEM,
                                    "%s Replicated Add received with Control_UUID=%s and Entry_UUID=%s.\n",
                                    sessionid, target_uuid,entry_uuid);
                            }

                            slapi_ch_free ((void**)&entry_uuid);
                        }
                    }
                }
            }
            else
            {
                PR_ASSERT(0);
            }
        }
        else
        {

        }
    }
    else
    {
        slapi_operation_set_csngen_handler ( op, (void*)replica_generate_next_csn );
    }

    copy_operation_parameters(pb);

    return SLAPI_PLUGIN_SUCCESS;
}
