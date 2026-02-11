compareTrue (Node *node, IFNode *left) {
    switch (left->opcode) {
    case opCMPEQ:
    case opCMPNE:
    case opCMPLT:
    case opCMPLE:
    case opCMPGT:
    case opCMPGE:

    case opCMPEQ_I:
    case opCMPNE_I:
    case opCMPLT_I:
    case opCMPLE_I:
    case opCMPGT_I:
    case opCMPGE_I:
        return left ;
    }
    return issue (new IFExpression (node, opCMPNE, left, zero)) ;
}
