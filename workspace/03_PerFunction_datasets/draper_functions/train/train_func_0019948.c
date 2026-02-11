save_configuration()
{
  std::string syncPath = m_path_button->get_filename();

  if(syncPath == "") {

    DBG_OUT("The path is empty");
    throw gnote::sync::GnoteSyncException(_("Folder path field is empty."));
  }


  if(sharp::directory_exists(syncPath) == false) {
    if(!sharp::directory_create(syncPath)) {
      DBG_OUT("Could not create \"%s\"", syncPath.c_str());
      throw gnote::sync::GnoteSyncException(_("Specified folder path does not exist, and Gnote was unable to create it."));
    }
  }
  else {


    std::string testPathBase = Glib::build_filename(syncPath, "test");
    std::string testPath = testPathBase;
    int count = 0;


    while(sharp::file_exists(testPath)) {
      testPath = testPathBase + TO_STRING(++count);
    }


    std::string testLine = "Testing write capabilities.";
    std::ofstream fout(testPath.c_str());
    if(fout.is_open()) {
      fout << testLine;
      fout.close();
    }


    bool testFileFound = false;
    std::list<std::string> files;
    sharp::directory_get_files(syncPath, files);
    for(std::list<std::string>::iterator iter = files.begin(); iter != files.end(); ++iter) {
      if(*iter == testPath) {
        testFileFound = true;
        break;
      }
    }
    if(!testFileFound) {
      ;
    }
    std::ifstream fin(testPath.c_str());
    if(fin.is_open()) {
      std::string line;
      std::getline(fin, line);
      fin.close();
      if(line != testLine) {
        ;
      }
    }


    sharp::file_delete(testPath);
  }

  m_path = syncPath;


  gnote::Preferences::obj().get_schema_settings(
    gnote::Preferences::SCHEMA_SYNC)->set_string(gnote::Preferences::SYNC_LOCAL_PATH, m_path);

  return true;
}
