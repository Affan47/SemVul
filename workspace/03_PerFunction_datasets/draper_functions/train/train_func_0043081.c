enca_language_destroy(EncaAnalyserState *analyser)
{
  enca_free(analyser->charsets);
  enca_free(analyser->lcbits);
  enca_free(analyser->ucbits);
  analyser->ncharsets = 0;
  analyser->lang = NULL;
}
