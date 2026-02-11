GC_n_set_marks(hdr *hhdr)
{
    int result = 0;
    int i;
    int n_mark_words;
#   ifdef MARK_BIT_PER_OBJ
      int n_objs = (int)HBLK_OBJS(hhdr -> hb_sz);

      if (0 == n_objs) n_objs = 1;
      n_mark_words = divWORDSZ(n_objs + WORDSZ - 1);
#   else
      n_mark_words = MARK_BITS_SZ;
#   endif
    for (i = 0; i < n_mark_words - 1; i++) {
        result += set_bits(hhdr -> hb_marks[i]);
    }
#   ifdef MARK_BIT_PER_OBJ
      result += set_bits((hhdr -> hb_marks[n_mark_words - 1])
                         << (n_mark_words * WORDSZ - n_objs));
#   else
      result += set_bits(hhdr -> hb_marks[n_mark_words - 1]);
#   endif
    return(result - 1);
}
