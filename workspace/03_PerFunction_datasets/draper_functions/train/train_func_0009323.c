router_nickname_is_in_list(const routerinfo_t *router, const char *list)
{
  smartlist_t *nickname_list;
  int v = 0;

  if (!list)
    return 0;
  tor_assert(router);

  nickname_list = smartlist_new();
  smartlist_split_string(nickname_list, list, ",",
    SPLIT_SKIP_SPACE|SPLIT_STRIP_SPACE|SPLIT_IGNORE_BLANK, 0);
  SMARTLIST_FOREACH(nickname_list, const char *, cp,
                    if (router_nickname_matches(router, cp)) {v=1;break;});
  SMARTLIST_FOREACH(nickname_list, char *, cp, tor_free(cp));
  smartlist_free(nickname_list);
  return v;
}
