MakeRfmStm(RfmBlock block, RfmStm prev, Node stm_node)
{
    RfmStm new;

    if (block == NULL) {
        return(NULL);
    }
    new = GET_RFM_STM_TABLE();
    new->stm_node = stm_node;
    while ((stm_node) &&
           (commonp->node_parent_tbl[stm_node->CODE] ==
                                                  NODE_PARENT_EXIST)) {
        if (stm_node->CODE == NODE_STMTH) {
             break;
        }
        stm_node = stm_node->PARENT_NODE;
    }
    if ((stm_node) &&
        (stm_node->CODE == NODE_STMTH)) {
        new->line_no = stm_node->stmth.line_no;
    }
    new->block = block;
    if (prev) {
        if (prev->next) {
            prev->next->prev = new;
        }
        new->next = prev->next;
        prev->next = new;
        new->prev = prev;
    } else {
        if (block->stm_list) {
            block->stm_list->prev = new;
        }
        new->next = block->stm_list;
        block->stm_list = new;
    }
    if (new->next == NULL) {
        block->stm_tail = new;
    }
    return(new);
}
