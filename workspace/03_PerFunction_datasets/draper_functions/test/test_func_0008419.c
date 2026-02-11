io_zero_padding_needs_dist(DescField *field,
                                       FILE *fp,
                                       EncdescIOFunc io_func)
{
  io_func(&field->has_zero_padding, sizeof (bool), (size_t) 1, fp);
  if (field->has_zero_padding) {
    io_func(&field->fieldlen_is_const, sizeof (bool), (size_t) 1, fp);
    if (field->fieldlen_is_const) {
      io_func(&field->len, sizeof (field->len), (size_t) 1, fp);
    }
    else {
      io_func(&field->max_zero, sizeof (field->max_zero), (size_t) 1, fp);
      return true;
    }
  }
  return false;
}
