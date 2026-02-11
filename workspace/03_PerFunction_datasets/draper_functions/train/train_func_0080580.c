tryParseDouble(const char *s, const char *s_end, double *result)
{
  if (s >= s_end)
  {
    return false;
  }

  double mantissa = 0.0;


  int exponent = 0;


  char sign = '+';
  char exp_sign = '+';
  char const *curr = s;


  int read = 0;

  bool end_not_reached = false;


  if (*curr == '+' || *curr == '-')
  {
    sign = *curr;
    curr++;
  }
  else if (isdigit(*curr)) {  }
  else
  {
    goto fail;
  }


  while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
  {
    mantissa *= 10;
    mantissa += static_cast<int>(*curr - 0x30);
    curr++; read++;
  }


  if (read == 0)
    goto fail;

  if (!end_not_reached)
    goto assemble;


  if (*curr == '.')
  {
    curr++;
    read = 1;
    while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
    {

      mantissa += static_cast<int>(*curr - 0x30) * pow(10, -read);
      read++; curr++;
    }
  }
  else if (*curr == 'e' || *curr == 'E') {}
  else
  {
    goto assemble;
  }

  if (!end_not_reached)
    goto assemble;


  if (*curr == 'e' || *curr == 'E')
  {
    curr++;

    if ((end_not_reached = (curr != s_end)) && (*curr == '+' || *curr == '-'))
    {
      exp_sign = *curr;
      curr++;
    }
    else if (isdigit(*curr)) {  }
    else
    {

      goto fail;
    }

    read = 0;
    while ((end_not_reached = (curr != s_end)) && isdigit(*curr))
    {
      exponent *= 10;
      exponent += static_cast<int>(*curr - 0x30);
      curr++; read++;
    }
    exponent *= (exp_sign == '+'? 1 : -1);
    if (read == 0)
      goto fail;
  }

assemble:
  *result = (sign == '+'? 1 : -1) * ldexp(mantissa * pow(5, exponent), exponent);
  return true;
fail:
  return false;
}
