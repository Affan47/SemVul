replace_array_in_array_du(Block *sb_block)
{
    Statement *stm;

    stm = sb_block->pre_head->stm_head;
    while(stm != NULL && stm->ope != OPE_CALL && stm->ope != OPE_FUNC){
        stm = stm->next;
    }

    replace_array_in_array_du_table(sb_block->def_use_lmad->MayUse, stm);
    replace_array_in_array_du_table(sb_block->def_use_lmad->MayMod, stm);
}
