arg_is_null(bool use_null_value)
{
  if (use_distinct_values)
  {
    const bool rc= table->field[0]->is_null();
    DBUG_ASSERT(!rc);
    return rc;
  }
  return use_null_value ?
    item_sum->args[0]->null_value :
    (item_sum->args[0]->maybe_null && item_sum->args[0]->is_null());
}
