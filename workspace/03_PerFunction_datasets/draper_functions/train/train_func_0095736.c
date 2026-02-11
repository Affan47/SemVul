make_token() {
  logParseToken *ret = malloc(sizeof(logParseToken));
  if (ret == NULL) return NULL;

  ret->type = 0;
  ret->optional = 0;
  ret->deterministic = 1;
  ret->logdatafield = 0;
  ret->string_before = "";
  ret->string_after = "";
  ret->string_len_before = 0;
  ret->string_len_after = 0;
  ret->parser = NULL;
  ret->next = NULL;

  maxTokenBufferSize++;

  return ret;
}
