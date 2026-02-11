merfun(field_t field1, field_t *field2, int function)
{
  if      ( function == func_min )  mermin(field1, field2);
  else if ( function == func_max )  mermax(field1, field2);
  else if ( function == func_sum )  mersum(field1, field2);
  else if ( function == func_mean ) mermean(field1, field2);
  else if ( function == func_avg )  meravg(field1, field2);
  else if ( function == func_std )  merstd(field1, field2);
  else if ( function == func_var )  mervar(field1, field2);
  else cdoAbort("function %d not implemented!", function);
}
