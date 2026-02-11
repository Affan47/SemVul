param_fixed_values_cmp (GParamSpec   *pspec,
                        const GValue *value1,
                        const GValue *value2)
{
  if (value1->data[0].v_int < value2->data[0].v_int)
    return -1;
  else
    return value1->data[0].v_int > value2->data[0].v_int;
}
