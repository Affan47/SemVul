geoip_get_request_history(geoip_client_action_t action)
{
  smartlist_t *entries, *strings;
  char *result;
  unsigned granularity = IP_GRANULARITY;

  if (action != GEOIP_CLIENT_NETWORKSTATUS &&
      action != GEOIP_CLIENT_NETWORKSTATUS_V2)
    return NULL;
  if (!geoip_countries)
    return NULL;

  entries = smartlist_new();
  SMARTLIST_FOREACH(geoip_countries, geoip_country_t *, c, {
      uint32_t tot = 0;
      c_hist_t *ent;
      tot = (action == GEOIP_CLIENT_NETWORKSTATUS) ?
            c->n_v3_ns_requests : c->n_v2_ns_requests;
      if (!tot)
        continue;
      ent = tor_malloc_zero(sizeof(c_hist_t));
      strlcpy(ent->country, c->countrycode, sizeof(ent->country));
      ent->total = round_to_next_multiple_of(tot, granularity);
      smartlist_add(entries, ent);
  });
  smartlist_sort(entries, _c_hist_compare);

  strings = smartlist_new();
  SMARTLIST_FOREACH(entries, c_hist_t *, ent, {
      smartlist_add_asprintf(strings, "%s=%u", ent->country, ent->total);
  });
  result = smartlist_join_strings(strings, ",", 0, NULL);
  SMARTLIST_FOREACH(strings, char *, cp, tor_free(cp));
  SMARTLIST_FOREACH(entries, c_hist_t *, ent, tor_free(ent));
  smartlist_free(strings);
  smartlist_free(entries);
  return result;
}
