Add( vtksys_stl::string name, const int* truth )
{
  if (
    ( ! this->StillAdding ) ||
    ( this->OriginalNames.size() >= this->Endings.size() ) ||
    ( ! this->CheckTruth( truth ) ) )
    {
    this->StillAdding = false;
    return false;
    }
  vtksys_stl::string::size_type len = name.size();
  if (
    ( len != this->Prefix.size() + 1 ) ||
    ( name.substr( 0, len - 1 ) != this->Prefix ) ||
    ( tolower( name[len - 1] ) != this->Endings[this->OriginalNames.size()] ) )
    {
    this->StillAdding = false;
    return false;
    }

  this->OriginalNames.push_back( name );
  return true;
}
