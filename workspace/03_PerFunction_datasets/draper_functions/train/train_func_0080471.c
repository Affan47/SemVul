DeleteRfmQuad(RfmQuad quad)
{
    int i;

    if (quad == NULL) {
        return;
    }
    if (quad->prev) {
        quad->prev->next = quad->next;
    } else {
        if (quad->stm) {
            quad->stm->quad_list = quad->next;
        } else {
            MSG_LOGICALERROR;
        }
    }
    if (quad->next) {
        quad->next->prev = quad->prev;
    } else {
        if (quad->stm) {
            quad->stm->quad_tail = quad->prev;
        } else {
            MSG_LOGICALERROR;
        }
    }
    for (i=0; i<4; i++) {
        DeleteRfmOperand(quad->operand[i]);
    }
    FREE_RFM_QUAD_TABLE(quad);
}
