parse_children_definition (void)
{
  this->get ();
  this->check_for_PE_reference ();
  int subelement_number = 0;
  ACEXML_Char nextch = this->peek();
  switch (nextch)
    {
      case '#':
        if (this->parse_token (ACE_TEXT ("#PCDATA")) < 0)
          {
            this->fatal_error(ACE_TEXT ("Expecting keyword '#PCDATA'"));
          }
        this->check_for_PE_reference ();
        nextch = this->get();
        while (nextch == '|')
          {
            this->check_for_PE_reference ();
            ACEXML_Char *name = this->parse_name ();

            ACE_UNUSED_ARG (name);
            ++subelement_number;

            this->check_for_PE_reference ();
            nextch = this->skip_whitespace();
          }
        if (nextch != ')' ||
            (subelement_number && this->get () != '*'))
          {
            this->fatal_error(ACE_TEXT ("Expecing ')' or ')*' at end of Mixed")
                              ACE_TEXT (" element"));
          }

        break;
      default:
        int status = this->parse_child (1);
        if (status != 0)
          return -1;
    }


  nextch = this->peek ();
  switch (nextch)
    {
      case '?':

        this->get ();
        break;
      case '*':

        this->get ();
        break;
      case '+':

        this->get ();
        break;
      default:
        break;
    }

  return 0;
}
