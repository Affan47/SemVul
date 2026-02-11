set_variable(THD *thd, Field *field, Item **value)
{
  if (!value)
  {
    field->set_null();
    return 0;
  }

  return sp_eval_expr(thd, field, value);
}
