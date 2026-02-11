phaseX_get (token_ty *tp)
{
  static bool middle;

  phase5_get (tp);

  if (tp->type == token_type_eoln || tp->type == token_type_eof)
    middle = false;
  else
    {
      if (middle)
        {

          if (tp->type == token_type_hash)
            tp->type = token_type_symbol;
        }
      else
        {


          if (tp->type == token_type_white_space)
            {
              token_ty next;

              phase5_get (&next);
              if (next.type == token_type_hash)
                *tp = next;
              else
                phase5_unget (&next);
            }
          middle = true;
        }
    }
}
