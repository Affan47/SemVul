receive_cleanup(void) {

  std::string full_dirname(prog_config.working_dir);
  full_dirname += "/faxin/current";
  int result = rmdir(full_dirname.c_str());

  if (result == -1 && errno == ENOTEMPTY) {


    struct stat statinfo;
    std::string file_name(full_dirname);
    file_name += "/current.001";
    if (!stat(file_name.c_str(), &statinfo)
	&& !statinfo.st_size) {
      unlink(file_name.c_str());
      rmdir(full_dirname.c_str());
    }
    else {
      std::pair<std::string, std::string> fax_info(save_received_fax());

      if (!fax_info.first.empty()) {
	received_fax_count++;
	fax_received_notify(fax_info);
      }
    }
  }
}
