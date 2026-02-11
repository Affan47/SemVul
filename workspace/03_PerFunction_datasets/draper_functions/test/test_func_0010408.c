cloneTree() {
    RBBINode    *n;

    if (fType == RBBINode::varRef) {


        n = fLeftChild->cloneTree();
    } else if (fType == RBBINode::uset) {
        n = this;
    } else {
        n = new RBBINode(*this);

        if (n != NULL) {
            if (fLeftChild != NULL) {
                n->fLeftChild          = fLeftChild->cloneTree();
                n->fLeftChild->fParent = n;
            }
            if (fRightChild != NULL) {
                n->fRightChild          = fRightChild->cloneTree();
                n->fRightChild->fParent = n;
            }
        }
    }
    return n;
}
