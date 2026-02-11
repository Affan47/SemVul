MakeInnerRfmBlock(RfmBlock outer, Node node)
{
    RfmBlock new;

    if (outer == NULL) {
        return(NULL);
    }
    new = GET_RFM_BLOCK_TABLE();
    new->block_kind = RFM_BLOCK_BB;
    new->node = node;
    new->module = RFM_ModuleCurrent;
    new->outer = outer;
    if (outer->inner) {
        new->next = outer->inner;
        outer->inner->prev = new;
    }
    outer->inner = new;
    return(new);
}
