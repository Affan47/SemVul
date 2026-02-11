badcharkey_utf(char ** wlst, const w_char * word, int wl, int ns, int cpdsuggest)
{
  w_char        tmpc;
  w_char        candidate_utf[MAXSWL];
  char          candidate[MAXSWUTF8L];
  memcpy(candidate_utf, word, wl * sizeof(w_char));


  for (int i=0; i < wl; i++) {
    tmpc = candidate_utf[i];

    mkallcap_utf(candidate_utf + i, 1, langnum);
    if (!w_char_eq(tmpc, candidate_utf[i])) {
       u16_u8(candidate, MAXSWUTF8L, candidate_utf, wl);
       ns = testsug(wlst, candidate, strlen(candidate), ns, cpdsuggest, NULL, NULL);
       if (ns == -1) return -1;
       candidate_utf[i] = tmpc;
    }

    if (!ckey) continue;
    w_char * loc = ckey_utf;
    while ((loc < (ckey_utf + ckeyl)) && !w_char_eq(*loc, tmpc)) loc++;
    while (loc < (ckey_utf + ckeyl)) {
       if ((loc > ckey_utf) && !w_char_eq(*(loc - 1), W_VLINE)) {
          candidate_utf[i] = *(loc - 1);
          u16_u8(candidate, MAXSWUTF8L, candidate_utf, wl);
          ns = testsug(wlst, candidate, strlen(candidate), ns, cpdsuggest, NULL, NULL);
          if (ns == -1) return -1;
       }
       if (((loc + 1) < (ckey_utf + ckeyl)) && !w_char_eq(*(loc + 1), W_VLINE)) {
          candidate_utf[i] = *(loc + 1);
          u16_u8(candidate, MAXSWUTF8L, candidate_utf, wl);
          ns = testsug(wlst, candidate, strlen(candidate), ns, cpdsuggest, NULL, NULL);
          if (ns == -1) return -1;
       }
       do { loc++; } while ((loc < (ckey_utf + ckeyl)) && !w_char_eq(*loc, tmpc));
    }
    candidate_utf[i] = tmpc;
  }
  return ns;
}
