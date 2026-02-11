link_omp_operand(Operand *oprs, Operand *opr)
{
    Operand *temp_opr;

    if( oprs == NULL ){
        return opr;
    }else {
        for( temp_opr = oprs; temp_opr->next; temp_opr = temp_opr->next );
        temp_opr->next = opr;
        opr->next = NULL;
        return( oprs );

    }
}
