reset_field()
{
  double nr= args[0]->val_real();
  uchar *res=result_field->ptr;

  if (maybe_null)
  {
    if (args[0]->null_value)
    {
      nr=0.0;
      result_field->set_null();
    }
    else
      result_field->set_notnull();
  }
  float8store(res,nr);
}
