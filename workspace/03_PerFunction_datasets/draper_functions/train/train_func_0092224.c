update_field()
{
  DBUG_ASSERT (aggr->Aggrtype() != Aggregator::DISTINCT_AGGREGATOR);
  if (hybrid_type == DECIMAL_RESULT)
  {
    my_decimal value, *arg_val= args[0]->val_decimal(&value);
    if (!args[0]->null_value)
    {
      if (!result_field->is_null())
      {
        my_decimal field_value,
                   *field_val= result_field->val_decimal(&field_value);
        my_decimal_add(E_DEC_FATAL_ERROR, dec_buffs, arg_val, field_val);
        result_field->store_decimal(dec_buffs);
      }
      else
      {
        result_field->store_decimal(arg_val);
        result_field->set_notnull();
      }
    }
  }
  else
  {
    double old_nr,nr;
    uchar *res=result_field->ptr;

    float8get(old_nr,res);
    nr= args[0]->val_real();
    if (!args[0]->null_value)
    {
      old_nr+=nr;
      result_field->set_notnull();
    }
    float8store(res,old_nr);
  }
}
