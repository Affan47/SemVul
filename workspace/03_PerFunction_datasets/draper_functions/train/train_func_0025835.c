find (const ACE_TCHAR *module_name) const
{
  ACE_TRACE ("ACE_Stream_Type::find");

  for (ACE_Module_Type *m = this->head_;
       m != 0;
       m = m->link ())
    if (ACE_OS::strcmp (m->name (), module_name) == 0)
      return m;

  return 0;
}
