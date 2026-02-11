CopyRfmOperand(RfmOperand operand, RfmStm stm)
{
    RfmOperand  new;
    RfmNodeLink new_link;
    RfmNodeLink link;

    if (operand == NULL) {
        return(NULL);
    }
    if (stm == NULL) {
        stm = operand->stm;
    }
    new = GET_RFM_OPERAND_TABLE();
    new->kind = operand->kind;
    new->tbl.var = operand->tbl.var;
    new->stm = stm;
    new_link = NULL;
    for (link = operand->node_link;
         link != NULL;
         link = link->next) {
        new_link = MakeRfmNodeLink(new, new_link, link->node);
        new_link->operand = CopyRfmOperand(link->operand, stm);
    }
    return(new);
}
