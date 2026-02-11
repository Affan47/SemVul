insert_stm_after_label( Pe_statement *pe_stm, Statement *ins_stm )
{
    Statement *stm;

    for( stm = pe_stm->stm_head;
         stm != NULL;
         stm = stm->next ){
        if( stm->ope != OPE_LABEL )
            break;
    }

    if( stm != NULL )
        insert_stm( pe_stm, stm->prev, ins_stm );
    else
        append_statement( &(pe_stm->stm_head), ins_stm );
}
