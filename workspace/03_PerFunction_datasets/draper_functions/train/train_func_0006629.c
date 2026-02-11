parse_number(char *string, STRLEN len, char **end)
{
    int seen_neg;
    int seen_dec;
    int seen_e;
    int seen_plus;
    int seen_digit;
    char *cp;

    seen_neg= seen_dec= seen_e= seen_plus= seen_digit= 0;

    if (len <= 0) {
        len= strlen(string);
    }

    cp= string;


    while (*cp && isspace(*cp))
      cp++;

    for ( ; *cp; cp++)
    {
      if ('-' == *cp)
      {
        if (seen_neg >= 2)
        {


          break;
        }
        seen_neg += 1;
      }
      else if ('.' == *cp)
      {
        if (seen_dec)
        {

          break;
        }
        seen_dec= 1;
      }
      else if ('e' == *cp)
      {
        if (seen_e)
        {

          break;
        }
        seen_e= 1;
      }
      else if ('+' == *cp)
      {
        if (seen_plus)
        {

          break;
        }
        seen_plus= 1;
      }
      else if (!isdigit(*cp))
      {


        break;
      }
    }

    *end= cp;


    if (len == 0 || cp - string < (int) len) {
        return -1;
    }

    return 0;
}
