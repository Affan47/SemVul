phase3_getc ()
{
  int lineno;
  int c;

  if (phase3_pushback_length)
    return phase3_pushback[--phase3_pushback_length];

  c = phase1_getc ();

  if (c == '#')
    {

      bool last_was_qmark = false;

      comment_start ();
      lineno = line_number;
      for (;;)
        {
          c = phase1_getc ();
          if (c == '\n' || c == EOF)
            {
              comment_line_end (0);
              break;
            }
          if (last_was_qmark && c == '>')
            {
              comment_line_end (1);
              skip_html ();
              break;
            }

          if (!(buflen == 0 && (c == ' ' || c == '\t')))
            comment_add (c);
          last_was_qmark = (c == '?' || c == '%');
        }
      last_comment_line = lineno;
      return '\n';
    }
  else if (c == '/')
    {
      c = phase1_getc ();

      switch (c)
        {
        default:
          phase1_ungetc (c);
          return '/';

        case '*':
          {

            bool last_was_star;

            comment_start ();
            lineno = line_number;
            last_was_star = false;
            for (;;)
              {
                c = phase1_getc ();
                if (c == EOF)
                  break;

                if (buflen == 0 && (c == ' ' || c == '\t'))
                  continue;
                comment_add (c);
                switch (c)
                  {
                  case '\n':
                    comment_line_end (1);
                    comment_start ();
                    lineno = line_number;
                    last_was_star = false;
                    continue;

                  case '*':
                    last_was_star = true;
                    continue;

                  case '/':
                    if (last_was_star)
                      {
                        comment_line_end (2);
                        break;
                      }


                  default:
                    last_was_star = false;
                    continue;
                  }
                break;
              }
            last_comment_line = lineno;
            return ' ';
          }

        case '/':
          {

            bool last_was_qmark = false;

            comment_start ();
            lineno = line_number;
            for (;;)
              {
                c = phase1_getc ();
                if (c == '\n' || c == EOF)
                  {
                    comment_line_end (0);
                    break;
                  }
                if (last_was_qmark && c == '>')
                  {
                    comment_line_end (1);
                    skip_html ();
                    break;
                  }

                if (!(buflen == 0 && (c == ' ' || c == '\t')))
                  comment_add (c);
                last_was_qmark = (c == '?' || c == '%');
              }
            last_comment_line = lineno;
            return '\n';
          }
        }
    }
  else
    return c;
}
