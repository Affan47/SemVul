compare_sem_node(Module_table *mpt,
                 const SemanticNode *lNode,
                 const SemanticNode *rNode)
{
    SemanticNode *node;
    Const_table *value;

    node = make_sem_node(mpt, OPE_SUB, lNode, rNode);
    node = process_sem_node(mpt, node);
    if(node->ope == OPE_INIT && node->ldata->data.leaf->kind == KIND_CONST){
        value = search_const_table(node->ldata->data.leaf->entry);
        DestructAllSemanticNode(node);
        switch(value->type){
        case TYPE_INT:
            if(value->val.i < 0) return -1;
            else if(value->val.i == 0) return 0;
            else return 1;
            break;
        case TYPE_REAL:
            if(value->val.r < 0) return -1;
            else if(value->val.r == 0) return 0;
            else return 1;
            break;
        case TYPE_DOUBLE:
            if(value->val.d < 0) return -1;
            else if(value->val.d == 0) return 0;
            else return 1;
            break;
        default:
            return SEMTREE_ERR;
            break;
        }
    } else {
        DestructAllSemanticNode(node);
        return SEMTREE_ERR;
    }
}
