delete_addp(RfmQuad quad)
{
    RfmOperand op;
    RfmTemp temp;

    RfmQuad quad_prev;
    RfmQuad quad_preprev;
    if ((quad->operator == OPE_ADDP) &&
        (op = quad->operand[2]) &&
        (op->kind == RFM_KIND_CONST) &&
        (op->tbl.cnst->attr == RFM_ATTR_INT) &&
        (op->tbl.cnst->csym_dict->CSYM_INT_CONST_VALUE == 0)) {
        if ((quad_prev = quad->prev) &&
            (quad_prev->operator == OPE_ADDP) &&
            (is_same_temp_operand(quad_prev->operand[0],
                                  quad->operand[1]))) {
            if ((quad_preprev = quad_prev->prev) &&
                (quad_preprev->operator == OPE_SUBSCRIPT) &&
                (is_same_temp_operand(quad_preprev->operand[0],
                                      quad_prev->operand[1]))) {
                temp = quad->operand[0]->tbl.temp;
                replace_temp_operand_inorder(quad->next,
                                         quad->operand[0] ,
                                         quad_prev->operand[0]);
                DeleteRfmQuad(quad);
                DeleteRfmTemp(temp);
                return quad_prev->operand[0];
            }
        }
    }
    return NULL;
}
