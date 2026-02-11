is_const_cond(const SemanticNode *node, int entry)
{
    return node->ldata->kind == LEAF
        && node->ldata->data.leaf->entry == entry
        && node->rdata->kind == LEAF
        && node->rdata->data.leaf->kind == KIND_CONST;
}
