is_pheader(SemiBlockRec* sbp)
{
    Statement*  stm = NULL;

    if (sbp->nsuc == 2) {
	for (stm = sbp->statement; stm != NULL; stm = stm->next) {
	    if ((stm->ope == OPE_JF || stm->ope == OPE_JT)
		&& stm->next == NULL) {
		break;
	    }
	}
    }

    return stm;
}
