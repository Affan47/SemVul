qr_shftal_cost(const Operand* op0, const Operand* op1, const Operand* op2)
{   int  cost;

    if  (op2->tbl.v->type != TYPE_INT
            ||  op1->tbl.v->type != TYPE_INT
            ||  op0->tbl.v->type != TYPE_INT)
    {   ERROR_TYPE_MISMATCH("SHFTAL");
    }

    cost = 0;
    if  (op2->kind == KIND_CONST)
    {   cost += load_operand_cost(op1, 0, TYPE_INT);
    }
    else
    {   cost += load_operand_cost(op2, 0, TYPE_INT);
        cost += load_operand_cost(op1, 0, TYPE_INT);
    }

    cost++;
    mark_register(op0, 0, TYPE_INT);

    return  cost;
}
