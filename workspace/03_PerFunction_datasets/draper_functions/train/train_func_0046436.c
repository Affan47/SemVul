back_letlive(httrackp * opt, cache_back * cache, struct_back * sback,
                 const int p) {
  lien_back *const back = sback->lnk;
  const int back_max = sback->count;
  int checkerror;
  htsblk *src = &back[p].r;

  assertf(p >= 0 && p < back_max);
  if (src && !src->is_file && src->soc != INVALID_SOCKET && src->statuscode >= 0
      && src->keep_alive_trailers == 0
      && !(checkerror = check_sockerror(src->soc))

    ) {
    htsblk tmp;

    memset(&tmp, 0, sizeof(tmp));

    back_connxfr(src, &tmp);
    back_delete(opt, cache, sback, p);

    back_connxfr(&tmp, src);
    src->req.flush_garbage = 1;
    return 1;
  }
  return 0;
}
