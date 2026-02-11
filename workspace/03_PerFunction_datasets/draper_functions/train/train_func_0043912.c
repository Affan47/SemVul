create_child(const char* name, CORBA::Context_out out)
{
  out = CORBA::Context::_nil();

  out = new ContextImpl(name, this);
}
