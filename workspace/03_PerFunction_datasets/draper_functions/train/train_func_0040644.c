OnTab(cmCursesMainForm* fm, WINDOW* w)
{
  if ( !this->GetString() )
    {
    return;
    }
  FORM* form = fm->GetForm();
  form_driver(form, REQ_NEXT_FIELD);
  form_driver(form, REQ_PREV_FIELD);
  std::string cstr = this->GetString();
  cstr = cstr.substr(0, cstr.find_last_not_of(" \t\n\r")+1);
  if ( this->LastString != cstr )
    {
    this->Cycle = false;
    this->CurrentIndex = 0;
    this->LastGlob = "";
    }
  std::string glob;
  if ( this->Cycle )
    {
    glob = this->LastGlob;
    }
  else
    {
    glob = cstr + "*";
    }
  std::vector<cmStdString> dirs;

  cmSystemTools::SimpleGlob(glob.c_str(), dirs, (this->Type == cmCacheManager::PATH?-1:0));
  if ( this->CurrentIndex < dirs.size() )
    {
    cstr = dirs[this->CurrentIndex];
    }
  if ( cstr[cstr.size()-1] == '*' )
    {
    cstr = cstr.substr(0, cstr.size()-1);
    }

  if ( cmSystemTools::FileIsDirectory(cstr.c_str()) )
    {
    cstr += "/";
    }

  this->SetString(cstr.c_str());
  touchwin(w);
  wrefresh(w);
  form_driver(form, REQ_END_FIELD);
  this->LastGlob = glob;
  this->LastString = cstr;
  this->Cycle = true;
  this->CurrentIndex ++;
  if ( this->CurrentIndex >= dirs.size() )
    {
    this->CurrentIndex = 0;
    }
}
