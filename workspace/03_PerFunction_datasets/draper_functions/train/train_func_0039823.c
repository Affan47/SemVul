parse_external_id (ACEXML_Char *&publicId,
                                  ACEXML_Char *&systemId)
{
  publicId = systemId = 0;
  ACEXML_Char nextch = this->get ();
  ACEXML_Char fwd = 0;
  switch (nextch)
    {
      case 'S':
        if (this->parse_token (ACE_TEXT ("YSTEM")) < 0 ||
            this->skip_whitespace_count () < 1)
          {
            this->fatal_error(ACE_TEXT ("Expecting keyword SYSTEM"));
          }
        if (this->parse_system_literal (systemId) != 0)
          {
            this->fatal_error(ACE_TEXT ("Invalid systemLiteral"));
          }
        break;
      case 'P':
        if (this->parse_token (ACE_TEXT ("UBLIC")) < 0 ||
            this->skip_whitespace_count () < 1)
          {
            this->fatal_error(ACE_TEXT ("Expecting keyword PUBLIC"));
          }
        if (this->parse_pubid_literal (publicId) != 0)
          {
            this->fatal_error(ACE_TEXT ("Invalid PubidLiteral"));
          }
        this->skip_whitespace_count(&fwd);
        if (fwd == '\'' || fwd == '"')
          {
            if (this->parse_system_literal (systemId) != 0)
              {
                this->fatal_error(ACE_TEXT ("Invalid systemLiteral"));
              }
          }
        else if (this->ref_state_ != ACEXML_ParserInt::IN_NOTATION)
          {
            this->fatal_error(ACE_TEXT ("Expecting systemLiteral after a ")
                              ACE_TEXT ("PUBLIC keyword"));
          }
        break;
      default:
        this->fatal_error(ACE_TEXT ("Invalid system/public Literal"));
    }
  return 0;
}
