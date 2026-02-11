fcsqrt_cost(symbol_type type)
{   int  cost;

#ifdef OUTPUT_TBL_OP_NAME
    printf("mathfunc name: %s\n",math_func_tbl[C_SQRT].math_func_name);
#endif
    cost = put_complex_or_dcomplex_cost( type, math_func_tbl[C_SQRT].cost[0],
			           math_func_tbl[C_SQRT].cost[1]);

    if ( cost <= -1 )
    {
        symbol_type temp_type;
        temp_type = (type == TYPE_COMPLEX) ? TYPE_REAL : TYPE_DOUBLE;

        cost = ope_cost_tbl[MUL].costs[1];
        cost += ope_cost_tbl[MUL].costs[1];
        cost += ope_cost_tbl[ADD].costs[1];
        cost += fsqrt_cost(temp_type);
        cost += fsqrt_cost(temp_type);
        cost += fatan2_cost(temp_type);
        cost += load_constant_cost(real_half_constant_entry(), 0, temp_type);
        cost += ope_cost_tbl[MUL].costs[1];
        cost += fcos_cost(temp_type);
        cost += fsin_cost(temp_type);
	cost += ope_cost_tbl[MUL].costs[1];
	cost += ope_cost_tbl[MUL].costs[1];
    }

    return  cost;
}
