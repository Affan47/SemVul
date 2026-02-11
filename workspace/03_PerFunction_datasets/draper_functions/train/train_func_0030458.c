GetFullName(const char* config, bool implib)
{
  if(this->IsImported())
    {
    return this->GetFullNameImported(config, implib);
    }
  else
    {
    return this->GetFullNameInternal(this->GetType(), config, implib);
    }
}
