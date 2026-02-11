classify_ks_search(const char **search)
{
  switch(**search)
    {
    case '*':
      (*search)++;
      return KS_SEARCH_SUBSTR;
    case '=':
      (*search)++;
      return KS_SEARCH_EXACT;
    case '<':
      (*search)++;
      return KS_SEARCH_MAIL;
    case '@':
      (*search)++;
      return KS_SEARCH_MAILSUB;
    case '0':
      if((*search)[1]=='x')
	{
	  if(strlen(*search)==10 && strspn(*search,HEX"x")==10)
	    {
	      (*search)+=2;
	      return KS_SEARCH_KEYID_SHORT;
	    }
	  else if(strlen(*search)==18 && strspn(*search,HEX"x")==18)
	    {
	      (*search)+=2;
	      return KS_SEARCH_KEYID_LONG;
	    }
	}

    default:


      if(strlen(*search)==8 && strspn(*search,HEX)==8)
	return KS_SEARCH_KEYID_SHORT;
      else if(strlen(*search)==16 && strspn(*search,HEX)==16)
	return KS_SEARCH_KEYID_LONG;


      return KS_SEARCH_SUBSTR;
    }
}
