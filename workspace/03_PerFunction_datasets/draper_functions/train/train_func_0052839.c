ProcessFromenvLocked(const string& flagval,
                                                   FlagSettingMode set_mode,
                                                   bool errors_are_fatal) {
  if (flagval.empty())
    return "";

  string msg;
  vector<string> flaglist;
  ParseFlagList(flagval.c_str(), &flaglist);

  for (size_t i = 0; i < flaglist.size(); ++i) {
    const char* flagname = flaglist[i].c_str();
    CommandLineFlag* flag = registry_->FindFlagLocked(flagname);
    if (flag == NULL) {
      error_flags_[flagname] = (string(kError) + "unknown command line flag"
                                + " '" + flagname + "'"
                                + " (via --fromenv or --tryfromenv)\n");
      undefined_names_[flagname] = "";
      continue;
    }

    const string envname = string("FLAGS_") + string(flagname);
    const char* envval = getenv(envname.c_str());
    if (!envval) {
      if (errors_are_fatal) {
        error_flags_[flagname] = (string(kError) + envname +
                                  " not found in environment\n");
      }
      continue;
    }


    if ((strcmp(envval, "fromenv") == 0) ||
        (strcmp(envval, "tryfromenv") == 0)) {
      error_flags_[flagname] = (string(kError) + "infinite recursion on " +
                                "environment flag '" + envval + "'\n");
      continue;
    }

    msg += ProcessSingleOptionLocked(flag, envval, set_mode);
  }
  return msg;
}
