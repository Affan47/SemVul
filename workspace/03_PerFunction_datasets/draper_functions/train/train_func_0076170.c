log_to_string(std::string& text) {

  if (logfile_name.empty()) return false;

  logfile.flush();
  text = "";
  std::ifstream infile;

  infile.open(logfile_name.c_str(), std::ios::in | std::ios:: binary);
  if (!infile) {
    new InfoDialog(gettext("Cannot open log file for reading"),
		   gettext("efax-gtk: print logfile"),
		   GTK_MESSAGE_ERROR,
		   parent_p,
		   true);


    return false;
  }
  const int BLOCKSIZE = 1024;
  char block[BLOCKSIZE];
  while (infile) {
    infile.read(block, BLOCKSIZE - 1);
    std::streamsize extracted = infile.gcount();
    if (extracted > 0) {
      block[extracted] = 0;
      text += block;
    }
  }
  return true;
}
