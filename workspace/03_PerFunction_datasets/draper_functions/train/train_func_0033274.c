phase8b_get (token_ty *tp)
{
  for (;;)
    {
      phase8a_get (tp);

      if (tp->type == token_type_white_space)
        continue;
      if (tp->type == token_type_eoln)
        {


          ++newline_count;
          if (last_non_comment_line > last_comment_line)
            savable_comment_reset ();
          continue;
        }
      break;
    }
}
