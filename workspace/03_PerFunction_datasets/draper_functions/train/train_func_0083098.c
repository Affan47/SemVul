val_decimal(my_decimal *val)
{
  my_decimal sum_buff, cnt;
  const my_decimal *sum_dec;
  DBUG_ASSERT(fixed == 1);
  if (aggr)
    aggr->endup();
  if (!count)
  {
    null_value=1;
    return NULL;
  }


  if (hybrid_type != DECIMAL_RESULT)
    return val_decimal_from_real(val);

  sum_dec= dec_buffs + curr_dec_buff;
  int2my_decimal(E_DEC_FATAL_ERROR, count, 0, &cnt);
  my_decimal_div(E_DEC_FATAL_ERROR, val, sum_dec, &cnt, prec_increment);
  return val;
}
