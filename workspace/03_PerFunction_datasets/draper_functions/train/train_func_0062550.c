qr_jump_cost(const Operand* op0)
{   int  cost;
    int jump_label_cost, jump_MT_cost;

    jump_label_cost = ope_cost_tbl[JMP].costs[0];
    jump_MT_cost = ope_cost_tbl[MJMP].costs[0];
    cost = 0;
    if  (op0->kind == KIND_LABEL)
    {
#ifdef OUTPUT_TBL_OP_NAME
        printf("operator name: %s\n",ope_cost_tbl[JMP].operator_name);
#endif
	cost += jump_label_cost;
	ope_count[JMP][0]++;
    }
    else if  (op0->kind == KIND_MT)
    {
#ifdef OUTPUT_TBL_OP_NAME
        printf("operator name: %s\n",ope_cost_tbl[MJMP].operator_name);
#endif
	cost += jump_MT_cost;
	ope_count[MJMP][0]++;
    }
    else
    {   ERROR_TYPE_MISMATCH("jump");
    }

    return  cost;
}
