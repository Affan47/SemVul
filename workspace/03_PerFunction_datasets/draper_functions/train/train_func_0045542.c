qr_intf_not_cost(const Operand* op0, const Operand* op1)
{
    int  cost = 0;

    if ((!is_integer(op0->tbl.v->type)
         && op0->tbl.v->type != TYPE_LOGICAL)
        || (!is_integer(op1->tbl.v->type)
            && op1->tbl.v->type != TYPE_LOGICAL)
        || op0->tbl.v->type != op1->tbl.v->type )
    {   ERROR_TYPE_MISMATCH("NOT");
    }

    cost += load_operand_cost(op1, 0, TYPE_INT);
    cost++;
    mark_register(op0, 0, TYPE_INT);
    return cost;
}
