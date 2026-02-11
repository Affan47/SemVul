save_queued_faxes(void) {


  std::string filename;
  {
    Thread::Mutex::Lock lock(working_dir_mutex);
    filename = working_dir;
  }
  filename += "/" SAVED_FAX_FILENAME;

  std::ofstream fileout(filename.c_str(), std::ios::out);
  if (!fileout) {
    std::string message("Can't open file ");
    message += filename;
    message += ", so the list of queued files can't be saved\n";
    write_error(message.c_str());
  }
  else {

#ifdef HAVE_STREAM_IMBUE
    fileout.imbue(std::locale::classic());
#endif

    FilenamesList::const_iterator iter;
    for (iter = filenames_s->begin(); iter != filenames_s->end(); ++iter) {
      fileout << iter->first << '?' << iter->second << '\n';
    }
    fileout << '!' << count << '\n';
  }
}
