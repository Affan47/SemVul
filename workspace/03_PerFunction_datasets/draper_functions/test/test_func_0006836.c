is_router_version_good_for_possible_guard(const char *platform)
{
  static int parsed_versions_initialized = 0;
  static tor_version_t first_good_0_2_1_guard_version;
  static tor_version_t first_good_0_2_2_guard_version;
  static tor_version_t first_good_later_guard_version;

  tor_version_t router_version;


  {
    char *s, *s2, *start;
    char tmp[128];

    tor_assert(platform);


    if (strcmpstart(platform,"Tor "))
      return 1;

    start = (char *)eat_whitespace(platform+3);
    if (!*start) return 0;
    s = (char *)find_whitespace(start);
    s2 = (char*)eat_whitespace(s);
    if (!strcmpstart(s2, "(r") || !strcmpstart(s2, "(git-"))
      s = (char*)find_whitespace(s2);

    if ((size_t)(s-start+1) >= sizeof(tmp))
      return 0;
    strlcpy(tmp, start, s-start+1);

    if (tor_version_parse(tmp, &router_version)<0) {
      log_info(LD_DIR,"Router version '%s' unparseable.",tmp);
      return 1;
    }
  }


  if (!parsed_versions_initialized) {


    tor_assert(tor_version_parse("0.2.1.31",
                                 &first_good_0_2_1_guard_version)>=0);
    tor_assert(tor_version_parse("0.2.2.34",
                                 &first_good_0_2_2_guard_version)>=0);
    tor_assert(tor_version_parse("0.2.3.6-alpha",
                                 &first_good_later_guard_version)>=0);


    parsed_versions_initialized = 1;
  }

  return ((tor_version_same_series(&first_good_0_2_1_guard_version,
                                   &router_version) &&
           tor_version_compare(&first_good_0_2_1_guard_version,
                               &router_version) <= 0) ||
          (tor_version_same_series(&first_good_0_2_2_guard_version,
                                   &router_version) &&
           tor_version_compare(&first_good_0_2_2_guard_version,
                               &router_version) <= 0) ||
          (tor_version_compare(&first_good_later_guard_version,
                               &router_version) <= 0));
}
