mailmime_type_write_driver(int (* do_write)(void *, const char *, size_t), void * data, int * col,
			       struct mailmime_type * type)
{
  int r;

  switch (type->tp_type) {
  case MAILMIME_TYPE_DISCRETE_TYPE:
    r = mailmime_discrete_type_write_driver(do_write, data, col, type->tp_data.tp_discrete_type);
    break;

  case MAILMIME_TYPE_COMPOSITE_TYPE:
    r = mailmime_composite_type_write_driver(do_write, data, col, type->tp_data.tp_composite_type);
    break;

  default:
    r = MAILIMF_ERROR_INVAL;
    break;
  }

  if (r != MAILIMF_NO_ERROR)
    return r;

  return MAILIMF_NO_ERROR;
}
