vlv_build_candidate_list( backend *be, struct vlvIndex* p, const struct vlv_request *vlv_request_control, IDList** candidates, struct vlv_response *vlv_response_control, int is_srchlist_locked, back_txn *txn)
{
    int return_value = LDAP_SUCCESS;
    DB *db = NULL;
    DBC *dbc = NULL;
    int rc, err;
    PRUint32 si = 0;
    PRUint32 length;
    int do_trim= 1;
    DB_TXN *db_txn = NULL;

    LDAPDebug(LDAP_DEBUG_TRACE,
              "=> vlv_build_candidate_list: %s %s Using VLV Index %s\n",
              slapi_sdn_get_dn(vlvIndex_getBase(p)), p->vlv_search->vlv_filter,
              vlvIndex_getName(p));
    if (!vlvIndex_online(p)) {
        if (is_srchlist_locked) {
            slapi_rwlock_unlock(be->vlvSearchList_lock);
        }
        return -1;
    }
    rc = dblayer_get_index_file(be, p->vlv_attrinfo, &db, 0);
    if (rc != 0) {

        LDAPDebug(LDAP_DEBUG_ANY, "VLV: can't get index file '%s' (err %d)\n",
                  p->vlv_attrinfo->ai_type, rc, 0);
        if (is_srchlist_locked) {
            slapi_rwlock_unlock(be->vlvSearchList_lock);
        }
        return -1;
    }

    length = vlvIndex_get_indexlength(p, db, 0 );


    vlvIndex_incrementUsage(p);

    if (is_srchlist_locked) {
        slapi_rwlock_unlock(be->vlvSearchList_lock);
    }
    if (txn) {
        db_txn = txn->back_txn_txn;
    }
    err = db->cursor(db, db_txn, &dbc, 0);
    if (err != 0) {

        LDAPDebug(LDAP_DEBUG_ANY, "VLV: couldn't get cursor (err %d)\n",
                  rc, 0, 0);
        return -1;
    }

    if (vlv_request_control)
    {
        switch(vlv_request_control->tag) {
        case 0:
            si = vlv_trim_candidates_byindex(length, vlv_request_control);
            break;
        case 1:
            si = vlv_build_candidate_list_byvalue(p, dbc, length, vlv_request_control);
            if (si==length) {
                do_trim = 0;

                *candidates = idl_alloc(1);
            }
            break;
        default:

            if (ISLEGACY(be)) {
                return_value = LDAP_OPERATIONS_ERROR;
            } else {
                return_value = LDAP_VIRTUAL_LIST_VIEW_ERROR;
            }
            break;
        }


        vlv_response_control->targetPosition = si + 1;
        vlv_response_control->contentCount = length;
        vlv_response_control->result = return_value;
    }

    if ((return_value == LDAP_SUCCESS) && do_trim) {

        PRUint32 start, stop;
        determine_result_range(vlv_request_control, si, length, &start, &stop);


        return_value = vlv_build_idl(start, stop, db, dbc, candidates, 0);
    }
    dbc->c_close(dbc);

    dblayer_release_index_file( be, p->vlv_attrinfo, db );
    return return_value;
}
