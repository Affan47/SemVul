first_run(gnote::NoteManager & manager)
{
  int to_import = 0;
  int imported = 0;
  bool success;

  DBG_OUT("import path is %s", m_tomboy_path.c_str());

  if(sharp::directory_exists(m_tomboy_path)) {
    std::list<std::string> files;
    sharp::directory_get_files_with_ext(m_tomboy_path, ".note", files);

    for(std::list<std::string>::const_iterator iter = files.begin();
        iter != files.end(); ++iter) {
      const std::string & file_path(*iter);

      to_import++;

      Note::Ptr note = manager.import_note(file_path);

      if(note) {
        DBG_OUT("success");
        success = true;
        imported++;
      }
    }
  }

  return success;
}
