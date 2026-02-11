compiler_simple_slice(struct compiler *c, slice_ty s, expr_context_ty ctx)
{
    int op = 0, slice_offset = 0, stack_count = 0;

    assert(s->v.Slice.step == NULL);
    if (s->v.Slice.lower) {
        slice_offset++;
        stack_count++;
        if (ctx != AugStore)
            VISIT(c, expr, s->v.Slice.lower);
    }
    if (s->v.Slice.upper) {
        slice_offset += 2;
        stack_count++;
        if (ctx != AugStore)
            VISIT(c, expr, s->v.Slice.upper);
    }

    if (ctx == AugLoad) {
        switch (stack_count) {
        case 0: ADDOP(c, DUP_TOP); break;
        case 1: ADDOP_I(c, DUP_TOPX, 2); break;
        case 2: ADDOP_I(c, DUP_TOPX, 3); break;
        }
    }
    else if (ctx == AugStore) {
        switch (stack_count) {
        case 0: ADDOP(c, ROT_TWO); break;
        case 1: ADDOP(c, ROT_THREE); break;
        case 2: ADDOP(c, ROT_FOUR); break;
        }
    }

    switch (ctx) {
    case AugLoad:
    case Load: op = SLICE; break;
    case AugStore:
    case Store: op = STORE_SLICE; break;
    case Del: op = DELETE_SLICE; break;
    case Param:
    default:
        PyErr_SetString(PyExc_SystemError,
                        "param invalid in simple slice");
        return 0;
    }

    ADDOP(c, op + slice_offset);
    return 1;
}
