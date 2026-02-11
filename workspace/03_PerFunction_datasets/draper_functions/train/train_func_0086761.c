RetrieveUnusedFlags(
    const set<const CommandLineFlagInfo *> &matching_flags,
    const NotableFlags &notable_flags,
    set<const CommandLineFlagInfo *> *unused_flags) {


  for (set<const CommandLineFlagInfo *>::const_iterator it =
        matching_flags.begin();
      it != matching_flags.end();
      ++it) {
    if (notable_flags.perfect_match_flag.count(*it) ||
        notable_flags.module_flags.count(*it) ||
        notable_flags.package_flags.count(*it) ||
        notable_flags.most_common_flags.count(*it) ||
        notable_flags.subpackage_flags.count(*it))
      continue;
    unused_flags->insert(*it);
  }
}
