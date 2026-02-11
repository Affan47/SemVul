AddFile(kwsys_stl::vector<kwsys_stl::string>& files, const char* file)
{
  if ( !this->Relative.empty() )
    {
    files.push_back(kwsys::SystemTools::RelativePath(this->Relative.c_str(), file));
    }
  else
    {
    files.push_back(file);
    }
}
