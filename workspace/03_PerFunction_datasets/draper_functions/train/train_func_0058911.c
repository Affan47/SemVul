recent_cb(std::string& rfile) {

  if (!Glib::file_test(rfile.c_str(), Glib::FILE_TEST_EXISTS)) {
    katoob_error(Utils::substitute(_("The file \"%s\" doesn't exist."), rfile.c_str()));
    return;
  }

  unsigned x = children.size();
  create_document(rfile, -1);
  if (children.size() != x) {
    _conf.recent_prepend(rfile);
    signal_recent_regenerate.emit();
  }
}
