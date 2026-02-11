block_has_jmp_stm(Block *block)
{
    Statement *s;

    if (block->pre_head == NULL)
	return FALSE;

    for (s = block->pre_head->stm_head; s != NULL; s = s->next) {
	if (s->ope == OPE_JMP)
	    return TRUE;
    }
    return FALSE;
}
