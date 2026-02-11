evalComparator(CmpOp_t ctok, int result)
{
    if (result == 0) {
        switch(ctok) {
        case CMP_OP_EQ:
        case CMP_OP_GE:
        case CMP_OP_LE:
            return LAS_EVAL_TRUE;
        case CMP_OP_NE:
        case CMP_OP_GT:
        case CMP_OP_LT:
            return LAS_EVAL_FALSE;
        default:
            return LAS_EVAL_INVALID;
        }
    } else if (result > 0) {
        switch(ctok) {
        case CMP_OP_GT:
        case CMP_OP_GE:
        case CMP_OP_NE:
            return LAS_EVAL_TRUE;
        case CMP_OP_LT:
        case CMP_OP_LE:
        case CMP_OP_EQ:
            return LAS_EVAL_FALSE;
        default:
            return LAS_EVAL_INVALID;
        }
    } else {
        switch(ctok) {
        case CMP_OP_LT:
        case CMP_OP_LE:
        case CMP_OP_NE:
            return LAS_EVAL_TRUE;
        case CMP_OP_GT:
        case CMP_OP_GE:
        case CMP_OP_EQ:
            return LAS_EVAL_FALSE;
        default:
            return LAS_EVAL_INVALID;
        }
    }
}
