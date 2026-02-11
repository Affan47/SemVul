substring_candidates(
    Slapi_PBlock    *pb,
    backend *be,
    Slapi_Filter    *f,
    int            *err,
    int            allidslimit
)
{
    char         *type, *initial, *final;
    char         **any;
    IDList       *idl;
    Slapi_Value  **ivals;
    int          unindexed = 0;
    unsigned int opnote = SLAPI_OP_NOTE_UNINDEXED;
    Slapi_Attr   sattr;
    back_txn     txn = {NULL};
    int          pr_idx = -1;

    LDAPDebug( LDAP_DEBUG_TRACE, "=> sub_candidates\n", 0, 0, 0 );

    if (slapi_filter_get_subfilt( f, &type, &initial, &any, &final ) != 0) {
        LDAPDebug( LDAP_DEBUG_ANY, "  slapi_filter_get_subfilt fails\n",
            0, 0, 0 );
        return( NULL );
    }


    slapi_attr_init(&sattr, type);
    slapi_attr_assertion2keys_sub_sv( &sattr, initial, any, final, &ivals );
    attr_done(&sattr);
    slapi_pblock_get(pb, SLAPI_PAGED_RESULTS_INDEX, &pr_idx);
    if ( ivals == NULL || *ivals == NULL ) {
        slapi_pblock_set( pb, SLAPI_OPERATION_NOTES, &opnote );
        pagedresults_set_unindexed( pb->pb_conn, pb->pb_op, pr_idx );
        LDAPDebug( LDAP_DEBUG_TRACE,
            "<= sub_candidates ALLIDS (no keys)\n", 0, 0, 0 );
        return( idl_allids( be ) );
    }


    slapi_pblock_get(pb, SLAPI_TXN, &txn.back_txn_txn);
    idl = keys2idl( pb, be, type, indextype_SUB, ivals, err, &unindexed, &txn, allidslimit );
    if ( unindexed ) {
        slapi_pblock_set( pb, SLAPI_OPERATION_NOTES, &opnote );
        pagedresults_set_unindexed( pb->pb_conn, pb->pb_op, pr_idx );
    }
    valuearray_free( &ivals );

    LDAPDebug( LDAP_DEBUG_TRACE, "<= sub_candidates %lu\n",
                   (u_long)IDL_NIDS(idl), 0, 0 );
    return( idl );
}
