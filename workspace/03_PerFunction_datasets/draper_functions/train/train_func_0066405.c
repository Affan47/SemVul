ShowUsageWithFlagsMatching(const char *argv0,
                                       const vector<string> &substrings) {
  fprintf(stdout, "%s: %s\n", Basename(argv0), ProgramUsage());

  vector<CommandLineFlagInfo> flags;
  GetAllFlags(&flags);

  string last_filename;
  bool first_directory = true;
  bool found_match = false;
  for (vector<CommandLineFlagInfo>::const_iterator flag = flags.begin();
       flag != flags.end();
       ++flag) {
    if (substrings.empty() ||
        FileMatchesSubstring(flag->filename, substrings)) {

      if (flag->description == kStrippedFlagHelp) continue;
      found_match = true;
      if (flag->filename != last_filename) {
        if (Dirname(flag->filename) != Dirname(last_filename)) {
          if (!first_directory)
            fprintf(stdout, "\n\n");
          first_directory = false;
        }
        fprintf(stdout, "\n  Flags from %s:\n", flag->filename.c_str());
        last_filename = flag->filename;
      }

      fprintf(stdout, "%s", DescribeOneFlag(*flag).c_str());
    }
  }
  if (!found_match && !substrings.empty()) {
    fprintf(stdout, "\n  No modules matched: use -help\n");
  }
}
