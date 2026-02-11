create_filename(const std::string& prefix, const std::string& postfix) {
  std::string fname (tdir_rep + "/" + prefix + "-" +
		kvu_numtostr(getpid()) + "-");
  struct stat statbuf;

  for(int n = 0; n < TEMPORARY_FILE_DIRECTORY::max_temp_files; n++) {
    if (is_valid() != true) break;

    std::string temp = fname + kvu_numtostr(tmp_index_rep) + postfix;
    if (tmp_index_rep > TEMPORARY_FILE_DIRECTORY::max_temp_files) tmp_index_rep = 0;
    ++tmp_index_rep;

    int res = lstat(temp.c_str(), &statbuf);
    if (res == -1 && errno == ENOENT) {

      return(temp);
    }

  }

  return("");
}
