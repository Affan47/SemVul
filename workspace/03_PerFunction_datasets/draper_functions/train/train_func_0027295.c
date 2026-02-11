get_realtime_directive(Block *block)
{
    Pe_statement *pe_stm;
    Statement *stm;
    Directive *dir;

    if (block->pre_head != NULL) {
	pe_stm = block->pre_head;
	for (stm = pe_stm->stm_head; stm != NULL; stm = stm->next) {
            for (dir = stm->dir_pre_head; dir != NULL; dir = dir->next) {
                Directive_id  dir_id = dir->func->id;
                if (dir_id == MFOR_REALTIME) {
                    return dir->func;
                }
            }
        }
    }
    return NULL;
}
