ParseAt(css, ci)
CSSContext css;
CSSInput ci;
{
  while (ci->cp < ci->ep)
  {
    if (*ci->cp == '{')
    {
      if ((ci->cp = ParseToChar(ci->cp + 1, ci->ep, '}', false)) == NULL)
      {
	ci->cp = ci->ep;
      }
      return(true);
    }
    else if (*ci->cp == ';')
    {
      ci->cp++;
      return(false);
    }
    ci->cp++;
  }

  return(true);
}
