qr_sign_cost(const Operand* op0, const Operand* op1, const Operand* op2)
{   int  cost;

    if  (op0->tbl.v->type != op1->tbl.v->type)
    {   ERROR_TYPE_MISMATCH("SIGN");
    }

    cost = load_operand_cost(op2, 0, TYPE_UNDEC);
    cost += load_operand_cost(op1, 0, TYPE_UNDEC);

    cost += ope_cost_tbl[EXOR].costs[0];
    mark_register(op0, 0, TYPE_UNDEC);

    cost++;
    cost += load_constant_cost(integer_zero_constant_entry(), 0, TYPE_INT);


    cost += 2;


    cost++;

    return  cost;
}
