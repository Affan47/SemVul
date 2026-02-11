p_set_stb_error(GapStoryBoard *stb, char *errtext)
{
  char *currline_string;


  if(stb->count_unprintable_chars < MAX_TOLERATED_UNPRINTABLE_CHARACTERS)
  {
    currline_string = p_dup_printable_stringprefix(stb, stb->currline, MAX_CHARS_ERRORTEXT_LONG);
    printf("** error: %s\n   [at line:%d] %s\n"
        , errtext
        , (int)stb->curr_nr
        , currline_string
        );
    g_free(currline_string);
  }

  if(stb->errtext == NULL)
  {
     if(errtext)
     {
       stb->errtext     = g_strdup(errtext);
     }
     else
     {
       stb->errtext     = g_strdup(_("internal error"));
     }
     stb->errline_nr  = stb->curr_nr;
     if(stb->currline)
     {
       stb->errline     = p_dup_printable_stringprefix(stb
                            , stb->currline
                            , MAX_CHARS_ERRORTEXT_GUI);
     }
  }
}
