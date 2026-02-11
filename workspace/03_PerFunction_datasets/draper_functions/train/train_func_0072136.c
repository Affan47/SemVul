put_real_or_double_cost (symbol_type type,
			     int real_cost, int double_cost)
{
    check_real_or_double (type);
    if (type == TYPE_REAL)
        return real_cost;
    else
        return double_cost;
}
