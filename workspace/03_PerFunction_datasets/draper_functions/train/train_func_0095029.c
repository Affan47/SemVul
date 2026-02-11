unlock_outer_jmp_sync( Block *receive, Block *pdom_mpb,
                       int total_pe, oneway_sync_type type )
{
    Pe_statement *pe0_stm = receive->pre_head;
    Pe_statement *pe1_stm = (pe0_stm != NULL) ? pe0_stm->next : NULL;
    Statement *stm1, *nstm0;
    Quadruple *qr1;
    Quadruple *syncr_qr = NULL;
    Quadruple *receive_qr = NULL;
    Quadruple *assign_qr;
    Const_table *eq_const;
    Var_table *sr_var = NULL;
    Sync_table *sr_sync = NULL, *ow_sync = NULL;
    Boolean set_flg = FALSE;

    if( pe1_stm == NULL || pdom_mpb == NULL )
        return;

    for( stm1 = pe1_stm->stm_head; stm1 && !set_flg; stm1 = stm1->next ){
        for( qr1 = stm1->qr_head; qr1 && !set_flg; qr1 = qr1->next ){
            if( qr1->ope == OPE_SYNCR ){
                syncr_qr = qr1;
                ow_sync = syncr_qr->op[0]->tbl.sync;
                set_flg = (receive_qr != NULL);
            }
            if( qr1->ope == OPE_RECEIVE ){
                receive_qr = qr1;
                sr_sync = receive_qr->op[0]->tbl.sync;
                sr_var =  receive_qr->op[1]->tbl.v;
                set_flg = (syncr_qr != NULL);
            }
        }
    }
    if( !set_flg ) return;

    if( type == SPB ){
        if( pdom_mpb->pre_head == NULL ){
            pdom_mpb->pre_head = alloc_pe_statement();
            pdom_mpb->pre_head->block = pdom_mpb;
            pdom_mpb->pre_head->vpe_no = 0;
        }
        pe0_stm = pdom_mpb->pre_head;

    }else if( type == bMPBs ){
        if( pdom_mpb->post_head == NULL ){
            pdom_mpb->post_head = alloc_pe_statement();
            pdom_mpb->post_head->block = pdom_mpb;
            pdom_mpb->post_head->vpe_no = 0;
        }
        pe0_stm = pdom_mpb->post_head;

    }else{
        assert(FALSE);
    }

    nstm0 = construct_statement( OPE_SEND, pe0_stm );
    eq_const = get_const_int( 0 );
    assign_qr = construct_vc_assign_qr( nstm0, sr_var, eq_const );
    append_qr( &(nstm0->qr_head), assign_qr );
    append_send_qr( nstm0, -1, sr_var, sr_sync );
    append_syncs_qr( nstm0, -1, ow_sync );

    insert_statement_after_label( pe0_stm, nstm0 );
}
