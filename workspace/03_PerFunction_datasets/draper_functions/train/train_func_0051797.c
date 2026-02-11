GetFilename(SizeType n) const
{
  if( n < Filenames.size() )
    return Filenames[n].c_str();
  return NULL;
}
