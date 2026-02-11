vorbis_book_clear(codebook *b) {
  if (b->decode_tree) {
    _ogg_free(b->decode_tree->tab);
    _ogg_free(b->decode_tree->tabl);

    _ogg_free(b->decode_tree->ptr0);
    _ogg_free(b->decode_tree->ptr1);
    memset(b->decode_tree, 0, sizeof(decode_aux));
    _ogg_free(b->decode_tree);
  }
  if (b->valuelist) _ogg_free(b->valuelist);
  if (b->codelist) _ogg_free(b->codelist);
  memset(b, 0, sizeof(codebook));
}
