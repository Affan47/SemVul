resolve (const char *name_in,
                             char *&value_out,
                             char *&type_out)
{
  ACE_TRACE ("ACE_Naming_Context::resolve");
  ACE_NS_WString val_str;

  if (this->resolve (ACE_NS_WString (name_in),
                     val_str,
                     type_out) == -1)
    return -1;


  value_out = val_str.char_rep ();

  return value_out == 0 ? -1 : 0;
}
