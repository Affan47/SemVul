SetDirectory(std::string const &dir, bool recursive)
{
  Directory dirList;
  unsigned int nfiles = dirList.Load(dir, recursive); (void)nfiles;

  Directory::FilenamesType const &filenames = dirList.GetFilenames();
  for( Directory::FilenamesType::const_iterator it = filenames.begin();
    it != filenames.end(); ++it)
    {
    AddFileName( *it );
    }
}
