ShowUsageWithFlagsRestrict(const char *argv0, const char *restrict) {
  vector<string> substrings;
  if (restrict != NULL && *restrict != '\0') {
    substrings.push_back(restrict);
  }
  ShowUsageWithFlagsMatching(argv0, substrings);
}
