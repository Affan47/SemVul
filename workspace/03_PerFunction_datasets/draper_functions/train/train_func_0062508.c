make_may_use_operand(Quadruple *qpt, Operand *op)
{
    Array_def_use_table *array_du;

    if(op->kind == KIND_ARRAY){
        array_du = make_array_du(op);
        subtract_array_def_use_table(&array_du,
                                     qpt->stm->pe_stm->block->Kill);
        if(qpt->stm->pe_stm->block->MayUse == NULL){
            qpt->stm->pe_stm->block->MayUse = array_du;
        } else {
            union_array_def_use_table(&(qpt->stm->pe_stm->block->MayUse),
                                      array_du);
        }
    }
}
