fix_uniprob_srilm(NGRAM_INFO *ndata, WORD_INFO *winfo)
{
  WORD_ID wb, we;

  wb = winfo->wton[winfo->head_silwid];
  we = winfo->wton[winfo->tail_silwid];
  if (ndata->d[0].prob[wb] == -99.0) {
    jlog("Warning: BOS word \"%s\" has unigram prob of \"-99\"\n", ndata->wname[wb]);
    jlog("Warning: assigining value of EOS word \"%s\": %f\n", ndata->wname[we], ndata->d[0].prob[we]);
    ndata->d[0].prob[wb] = ndata->d[0].prob[we];
  } else if (ndata->d[0].prob[we] == -99.0) {
    jlog("Warning: EOS word \"%s\" has unigram prob of \"-99\"\n", ndata->wname[we]);
    jlog("Warning: assigining value of BOS word \"%s\": %f\n", ndata->wname[wb], ndata->d[0].prob[wb]);
    ndata->d[0].prob[we] = ndata->d[0].prob[wb];
  }
}
