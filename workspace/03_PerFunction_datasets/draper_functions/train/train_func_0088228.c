pt_prepare_proxy_list_for_config_read(void)
{
  if (!managed_proxy_list)
    return;

  assert_unconfigured_count_ok();
  SMARTLIST_FOREACH_BEGIN(managed_proxy_list, managed_proxy_t *, mp) {

    if (mp->conf_state != PT_PROTO_COMPLETED) {
      SMARTLIST_DEL_CURRENT(managed_proxy_list, mp);
      managed_proxy_destroy(mp, 1);
      unconfigured_proxies_n--;
      continue;
    }

    tor_assert(mp->conf_state == PT_PROTO_COMPLETED);

    mp->marked_for_removal = 1;
    mp->got_hup = 1;
    SMARTLIST_FOREACH(mp->transports_to_launch, char *, t, tor_free(t));
    smartlist_clear(mp->transports_to_launch);
  } SMARTLIST_FOREACH_END(mp);

  assert_unconfigured_count_ok();

  tor_assert(unconfigured_proxies_n == 0);
}
