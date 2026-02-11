StartInternal( vtksys_stl::string name, const int*, int )
{
  vtksys_stl::string::size_type len = name.size();
  if ( len > 1 && tolower( name[len - 1] ) == this->Endings[0] )
    {
    this->Prefix = name.substr( 0, len - 1 );
    this->OriginalNames.push_back( name );
    this->StillAdding = true;
    return true;
    }
  this->StillAdding = false;
  this->Prefix = "";
  return false;
}
