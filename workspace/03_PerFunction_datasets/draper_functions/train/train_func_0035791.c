entry() const
{
  const char* ret = this->options().entry();
  if (ret == NULL)
    ret = parameters->target().entry_symbol_name();
  return ret;
}
