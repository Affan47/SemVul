calcNullable(RBBINode *n) {
    if (n == NULL) {
        return;
    }
    if (n->fType == RBBINode::setRef ||
        n->fType == RBBINode::endMark ) {

        n->fNullable = FALSE;
        return;
    }

    if (n->fType == RBBINode::lookAhead || n->fType == RBBINode::tag) {


        n->fNullable = TRUE;
        return;
    }


    calcNullable(n->fLeftChild);
    calcNullable(n->fRightChild);


    if (n->fType == RBBINode::opOr) {
        n->fNullable = n->fLeftChild->fNullable || n->fRightChild->fNullable;
    }
    else if (n->fType == RBBINode::opCat) {
        n->fNullable = n->fLeftChild->fNullable && n->fRightChild->fNullable;
    }
    else if (n->fType == RBBINode::opStar || n->fType == RBBINode::opQuestion) {
        n->fNullable = TRUE;
    }
    else {
        n->fNullable = FALSE;
    }
}
