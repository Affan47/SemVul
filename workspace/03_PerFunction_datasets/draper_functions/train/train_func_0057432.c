dse_search(Slapi_PBlock *pb)
{
    int scope;
    Slapi_Filter *filter;
    char **attrs;
    int attrsonly;

    struct dse* pdse;
    int returncode= LDAP_SUCCESS;
    int isrootdse= 0;
    char returntext[SLAPI_DSE_RETURNTEXT_SIZE]= "";
	Slapi_DN *basesdn = NULL;
	int estimate = 0;


    if (slapi_pblock_get( pb, SLAPI_PLUGIN_PRIVATE, &pdse ) < 0 ||
        slapi_pblock_get( pb, SLAPI_SEARCH_TARGET_SDN, &basesdn ) < 0 ||
        slapi_pblock_get( pb, SLAPI_SEARCH_SCOPE, &scope ) < 0 ||
        slapi_pblock_get( pb, SLAPI_SEARCH_FILTER, &filter ) < 0 ||
        slapi_pblock_get( pb, SLAPI_SEARCH_ATTRS, &attrs ) < 0 ||
        slapi_pblock_get( pb, SLAPI_SEARCH_ATTRSONLY, &attrsonly ) <0)
    {
        slapi_send_ldap_result( pb, LDAP_OPERATIONS_ERROR, NULL, NULL, 0, NULL );
        return(-1);
    }


    isrootdse= slapi_sdn_isempty(basesdn);

    switch(scope)
    {
    case LDAP_SCOPE_BASE:
        {
		Slapi_Entry *baseentry= NULL;
	    baseentry = dse_get_entry_copy(pdse, basesdn, DSE_USE_LOCK);
        if ( baseentry == NULL )
        {
            slapi_send_ldap_result( pb, LDAP_NO_SUCH_OBJECT, NULL, NULL, 0, NULL );
			slapi_log_error(SLAPI_LOG_PLUGIN,"dse_search", "node %s was not found\n",
								 slapi_sdn_get_dn(basesdn));
            return -1;
        }


        if(slapi_vattr_filter_test( pb, baseentry, filter, !isrootdse  )==0)
        {

            if(dse_call_callback(pdse, pb, SLAPI_OPERATION_SEARCH,
					DSE_FLAG_PREOP, baseentry, NULL, &returncode, returntext)
					== SLAPI_DSE_CALLBACK_OK)
            {
				dse_search_set *ss;
				ss = dse_search_set_new ();
				slapi_pblock_set (pb, SLAPI_SEARCH_RESULT_SET, ss);
				dse_search_set_add_entry (ss, baseentry);
				baseentry= NULL;
				estimate = 1;
        	}
        }
		slapi_entry_free(baseentry);
		}
        break;
    case LDAP_SCOPE_ONELEVEL:

    case LDAP_SCOPE_SUBTREE:
        if(!isrootdse)
        {
            estimate = do_dse_search(pdse, pb, scope, basesdn, filter, attrs, attrsonly);
        }
        break;
    }
	slapi_pblock_set (pb, SLAPI_SEARCH_RESULT_SET_SIZE_ESTIMATE, &estimate);


    return 0;
}
