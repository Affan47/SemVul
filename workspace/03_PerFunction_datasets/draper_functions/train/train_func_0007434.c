WalkPreOrder(Node node, void (*func)(Node))
{
    Node child;

    if (node == NULL) {
        return;
    }

    (*func)(node);

    switch (commonp->node_num_tbl[node->CODE]) {
    case NODE_CHILD_NONE:
        break;
    case NODE_CHILD_ONE:
        WalkPreOrder(node->FIRST_CHILD, func);
        break;
    case NODE_CHILD_TWO:
        WalkPreOrder(node->FIRST_CHILD, func);
        WalkPreOrder(node->SECOND_CHILD, func);
        break;
    case NODE_CHILD_THREE:
        WalkPreOrder(node->FIRST_CHILD, func);
        WalkPreOrder(node->SECOND_CHILD, func);
        WalkPreOrder(node->THIRD_CHILD, func);
        break;
    case NODE_CHILD_VAR:
        child = node->HEAD_CHILD;
        while (child) {
            WalkPreOrder(child, func);
            NODE_FORWARD(child);
        }
        break;
    default:
        MSG_LOGICALERROR;
        return;
    }
}
