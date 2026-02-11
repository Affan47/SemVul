parse_doctypedecl (void)
{
  if (this->parse_token (ACE_TEXT ("DOCTYPE")) < 0)
    {
      this->fatal_error(ACE_TEXT ("Expecting keyword DOCTYPE in a doctypedecl"));
    }

  ACEXML_Char nextch = 0;
  if (this->skip_whitespace_count (&nextch) == 0)
    {
      this->fatal_error(ACE_TEXT ("Expecting a space between DOCTYPE keyword ")
                        ACE_TEXT ("and name"));
    }

  this->doctype_ = this->parse_name ();
  if (this->doctype_ == 0)
    {
      this->fatal_error(ACE_TEXT ("Invalid DOCTYPE name"));
    }
  int count = this->skip_whitespace_count (&nextch);

  if (nextch == 'S' || nextch == 'P')
    {
      if (count == 0)
        {
          this->fatal_error(ACE_TEXT ("Expecting a space between DOCTYPE")
                            ACE_TEXT ("keyword and name"));
        }
      this->external_dtd_ = 1;
      this->parse_external_dtd ();
    }

  nextch = this->skip_whitespace ();
  switch (nextch)
    {
      case '[':
        this->internal_dtd_ = 1;
        this->parse_internal_dtd ();
        break;
      case '>':

        if (this->validate_ && !this->external_dtd_)
          {
            this->fatal_error (ACE_TEXT ("No DTD defined"));
          }
        return 0;
      case '0':
        this->fatal_error (ACE_TEXT ("Unexpected end-of-file"));
      default:
        break;
    }

  if (this->skip_whitespace() != '>')
    {
      this->fatal_error(ACE_TEXT ("Expecting '>' at end of doctypedecl"));
    }
  return 0;
}
