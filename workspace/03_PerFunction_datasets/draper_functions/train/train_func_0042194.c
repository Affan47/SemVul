add_bigram(FILE *fp, NGRAM_INFO *ndata)
{
  WORD_ID w[2], wtmp;
  LOGPROB prob;
  NNID bi_count = 0;
  NNID n2;
  boolean ok_p = TRUE;
  char *s;

  ndata->p_2 = (LOGPROB *)mymalloc_big(sizeof(LOGPROB), ndata->d[1].totalnum);

  while (getl(buf, sizeof(buf), fp) != NULL && buf[0] != '\\') {
    strcpy(pbuf, buf);
    if ( ++bi_count % 100000 == 0) {
      jlog("Stat: ngram_read_arpa: 2-gram read %lu (%d%%)\n", bi_count, bi_count * 100 / ndata->d[1].totalnum);
    }
    if ((s = strtok(buf, DELM)) == NULL) {
      jlog("Error: ngram_read_arpa: 2-gram: failed to parse, corrupted or invalid data?\n");
      return FALSE;
    }
    prob = (LOGPROB)atof(s);
    if ((s = strtok(NULL, DELM)) == NULL) {
      jlog("Error: ngram_read_arpa: 2-gram: failed to parse, corrupted or invalid data?\n");
      return FALSE;
    }
    w[0] = ngram_lookup_word(ndata, s);
    if (w[0] == WORD_INVALID) {
      jlog("Error: ngram_read_arpa: 2-gram #%lu: \"%s\": \"%s\" not exist in 1-gram\n", bi_count, pbuf, s);
      ok_p = FALSE;
      continue;
    }
    if ((s = strtok(NULL, DELM)) == NULL) {
      jlog("Error: ngram_read_arpa: 2-gram: failed to parse, corrupted or invalid data?\n");
      return FALSE;
    }
    w[1] = ngram_lookup_word(ndata, s);
    if (w[1] == WORD_INVALID) {
      jlog("Error: ngram_read_arpa: 2-gram #%lu: \"%s\": \"%s\" not exist in 1-gram\n", bi_count, pbuf, s);
      ok_p = FALSE;
      continue;
    }
    if (ndata->dir == DIR_RL) {

      wtmp = w[0];
      w[0] = w[1];
      w[1] = wtmp;
    }
    n2 = search_ngram(ndata, 2, w);
    if (n2 == NNID_INVALID) {
      jlog("Warning: ngram_read_arpa: 2-gram #%d: \"%s\": (%s,%s) not exist in LR 2-gram (ignored)\n", n2+1, pbuf, ndata->wname[w[0]], ndata->wname[w[1]]);
    } else {
      ndata->p_2[n2] = prob;
    }
  }

  if (ok_p == TRUE) {
    jlog("Stat: ngram_read_arpa: 2-gram read %lu end\n", bi_count);
  }

  return ok_p;
}
