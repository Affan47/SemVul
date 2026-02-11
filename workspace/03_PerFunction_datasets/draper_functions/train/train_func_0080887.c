is_in_system_directory() const
{
  if (this->is_in_sysroot())
    return true;
  return parameters->options().is_in_system_directory(this->filename());
}
