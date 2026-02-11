StartInternal( vtksys_stl::string name, const int*, int )
{
  vtksys_stl::string::size_type len = name.size();
  if ( ( len > (unsigned) this->Rank ) &&
    vtksys::SystemTools::LowerCase( name.substr(len - this->Rank ) ) == this->Endings.substr( 0, this->Rank ) )
    {
    this->Prefix = name.substr( 0, len - this->Rank );
    this->OriginalNames.push_back( name );
    this->StillAdding = true;
    return true;
    }
  this->Prefix = "";
  this->StillAdding = false;
  return false;
}
