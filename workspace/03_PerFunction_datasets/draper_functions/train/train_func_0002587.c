StableSort(std::vector<std::string> const & filenames)
{


  if( filenames.empty() || !SortFunc )
    {
    Filenames.clear();
    return true;
    }

  std::vector< SmartPointer<FileWithName> > filelist;
  filelist.resize( filenames.size() );

  std::vector< SmartPointer<FileWithName> >::iterator it2 = filelist.begin();
  for( Directory::FilenamesType::const_iterator it = filenames.begin();
    it != filenames.end(), it2 != filelist.end(); ++it, ++it2)
    {
    gdcm::Reader reader;
    reader.SetFileName( it->c_str() );
    SmartPointer<FileWithName> &f = *it2;
    if( reader.Read() )
      {
      f = new FileWithName( reader.GetFile() );
      f->filename = *it;
      }
    else
      {
      f = NULL;
      }
    }
  SortFunctor sf;
  sf = Sorter::SortFunc;
  std::stable_sort( filelist.begin(), filelist.end(), sf);

  Filenames.clear();
  for(it2 = filelist.begin(); it2 != filelist.end(); ++it2 )
    {
    SmartPointer<FileWithName> const & f = *it2;
    Filenames.push_back( f->filename );
    }

  return true;
}
