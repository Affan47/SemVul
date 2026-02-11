integer() const
{
  switch (_type)
  {
  case GEARMAN_RESULT_BINARY:
    return atoll(value.string.value());

  case GEARMAN_RESULT_BOOLEAN:
    return value._boolean;

  case GEARMAN_RESULT_INTEGER:
    return value._integer;

  case GEARMAN_RESULT_NULL:
    return 0;
  }

  return 0;
}
