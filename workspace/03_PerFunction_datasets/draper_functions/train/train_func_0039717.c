back_add_if_not_exists(struct_back * sback, httrackp * opt,
                           cache_back * cache, char *adr, char *fil, char *save,
                           char *referer_adr, char *referer_fil, int test) {
  back_clean(opt, cache, sback);
  if (!back_exist(sback, opt, adr, fil, save)) {
    return back_add(sback, opt, cache, adr, fil, save, referer_adr, referer_fil,
                    test);
  }
  return 0;
}
