dec_data_funcp(Operand *op)
{
    Data_node  *dnpt;

    dnpt = alloc_data_node();
    dnpt->times = 1;
    dnpt->type = TYPE_PTR;
    switch(op->kind) {
    case KIND_FUNC:
    case KIND_SUB:
    case KIND_INTFUNC:
        dnpt->val.p = op;
        break;
    default:
        assert(FALSE && "op->kind != (KIND_FUNC KIND_SUB KIND_INTFUNC)");
        break;
    }
    return dnpt;
}
