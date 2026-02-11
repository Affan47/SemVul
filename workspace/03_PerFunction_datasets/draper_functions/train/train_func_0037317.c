read_state_lang_bitmap (lang_bitmap *bitmap)
{
  struct state_token_st *t;

  t = peek_state_token (0);
  if (state_token_kind (t) == STOK_INTEGER)
    {
      *bitmap = t->stok_un.stok_num;
      next_state_tokens (1);
    }
  else
    {
      fatal_reading_state (t, "Bad syntax for bitmap");
    }
}
