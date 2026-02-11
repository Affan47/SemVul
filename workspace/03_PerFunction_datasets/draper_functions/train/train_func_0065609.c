kvp_value_get_numeric(const KvpValue * value)
{
    if (!value) return gnc_numeric_zero ();
    if (value->type == KVP_TYPE_NUMERIC)
    {
        return value->value.numeric;
    }
    else
    {
        return gnc_numeric_zero ();
    }
}
