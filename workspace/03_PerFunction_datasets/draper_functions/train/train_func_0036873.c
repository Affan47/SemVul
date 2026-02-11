CommandlineFlagsIntoString() {
  vector<CommandLineFlagInfo> sorted_flags;
  GetAllFlags(&sorted_flags);
  return TheseCommandlineFlagsIntoString(sorted_flags);
}
