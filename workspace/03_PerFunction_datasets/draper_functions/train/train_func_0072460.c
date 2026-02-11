RemoveAlias( wxString const &name )
{
  std::map<wxString,wxString>::iterator i = alias_.find(name);
  if( i != alias_.end() )
  {
    alias_.erase( i );
    return true;
  }
  return false;
}
