cet_char_to_ucs4(const char src, const cet_cs_vec_t* vec, int* value)
{
  int trash, c;
  int* dest;

  c = ((unsigned char)src & 0xFF);
  dest = (value != NULL) ? value : &trash;

  *dest = c;
  c -= vec->ucs4_offset;

  if (c < 0) {
    return CET_SUCCESS;
  } else if ((c >= vec->ucs4_count) || (vec->ucs4_map[c] == -1)) {
    return CET_ERROR;
  } else {
    *dest = vec->ucs4_map[c];
    return CET_SUCCESS;
  }
}
