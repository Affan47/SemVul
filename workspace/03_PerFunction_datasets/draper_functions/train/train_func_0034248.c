get_dyn_any()
{
  CHECK_NOT_DESTROYED;
  CORBA::Any value;
  value <<= readCurrent(CORBA::tk_any);
  return factory_create_dyn_any(value);
}
