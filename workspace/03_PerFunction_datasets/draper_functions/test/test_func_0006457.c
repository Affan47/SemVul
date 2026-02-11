ReadLinuxLsbRelease() {
  CritScope cs(&lsb_release_string_critsec);
  if (!lsb_release_string.empty()) {

    return lsb_release_string;
  }

  POpenStream lsb_release_output;
  if (!lsb_release_output.Open("lsb_release -idrcs", "r", NULL)) {
    LOG_ERR(LS_ERROR) << "Can't run lsb_release";
    return lsb_release_string;
  }

  std::ostringstream sstr;
  std::string line;
  int wait_status;

  if (!ExpectLineFromStream(&lsb_release_output, &line)) {
    return lsb_release_string;
  }
  sstr << "DISTRIB_ID=" << line;

  if (!ExpectLineFromStream(&lsb_release_output, &line)) {
    return lsb_release_string;
  }
  sstr << " DISTRIB_DESCRIPTION=\"" << line << '"';

  if (!ExpectLineFromStream(&lsb_release_output, &line)) {
    return lsb_release_string;
  }
  sstr << " DISTRIB_RELEASE=" << line;

  if (!ExpectLineFromStream(&lsb_release_output, &line)) {
    return lsb_release_string;
  }
  sstr << " DISTRIB_CODENAME=" << line;


  ExpectEofFromStream(&lsb_release_output);

  lsb_release_output.Close();
  wait_status = lsb_release_output.GetWaitStatus();
  if (wait_status == -1 ||
      !WIFEXITED(wait_status) ||
      WEXITSTATUS(wait_status) != 0) {
    LOG(LS_WARNING) << "Unexpected exit status from lsb_release";
  }

  lsb_release_string = sstr.str();

  return lsb_release_string;
}
