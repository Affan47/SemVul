ProcessDirectory(kwsys_stl::string::size_type start,
  const kwsys_stl::string& dir)
{

  bool last = ( start == this->Internals->Expressions.size()-1 );
  if ( last && this->Recurse )
    {
    this->RecurseDirectory(start, dir);
    return;
    }

  if ( start >= this->Internals->Expressions.size() )
    {
    return;
    }

  kwsys::Directory d;
  if ( !d.Load(dir.c_str()) )
    {
    return;
    }
  unsigned long cc;
  kwsys_stl::string fullname;
  kwsys_stl::string realname;
  kwsys_stl::string fname;
  for ( cc = 0; cc < d.GetNumberOfFiles(); cc ++ )
    {
    fname = d.GetFile(cc);
    if ( strcmp(fname.c_str(), ".") == 0 ||
      strcmp(fname.c_str(), "..") == 0  )
      {
      continue;
      }

    if ( start == 0 )
      {
      realname = dir + fname;
      }
    else
      {
      realname = dir + "/" + fname;
      }

#if defined(KWSYS_GLOB_CASE_INDEPENDENT)

    fname = kwsys::SystemTools::LowerCase(fname);
#endif

    if ( start == 0 )
      {
      fullname = dir + fname;
      }
    else
      {
      fullname = dir + "/" + fname;
      }


    if ( !last &&
      !kwsys::SystemTools::FileIsDirectory(realname.c_str()) )
      {
      continue;
      }

    if ( this->Internals->Expressions[start].find(fname.c_str()) )
      {
      if ( last )
        {
        this->AddFile(this->Internals->Files, realname.c_str());
        }
      else
        {
        this->ProcessDirectory(start+1, realname + "/");
        }
      }
    }
}
