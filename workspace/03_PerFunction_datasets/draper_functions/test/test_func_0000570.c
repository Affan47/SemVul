stm_is_do_write(const Statement *spt)
{
    Quadruple  *qpt;

    if (spt->ope == OPE_WRITE) {
        for (qpt = spt->qr_head; qpt != NULL; qpt = qpt->next) {
            if (qpt->ope == OPE_DO)
                return TRUE;
        }
    }

    return FALSE;
}
