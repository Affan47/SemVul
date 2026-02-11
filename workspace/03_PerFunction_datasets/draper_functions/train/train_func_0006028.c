__my_strtod(char *nptr, char **endptr, int32 *errnum)
{
 register char *s;
 short int sign;
 long int tmpexp;
 int32 got_dot, got_digit, save;
 long int exponent;
 double num;
 char *end;

 if (nptr == NULL) goto noconv;
 s = nptr;
 if (*s == '\0') goto noconv;


 while (isspace(*s)) s++;

 sign = *s == '-' ? -1 : 1;
 if (*s == '-' || *s == '+') s++;

 num = 0.0;
 got_dot = 0;
 got_digit = 0;
 exponent = 0;
 for (;; s++)
  {
   if (isdigit(*s))
    {
     got_digit = 1;

     if (num > MY_MAXDOUBLE * 0.1) exponent++;
      else num = 10.0*num + (*s - '0');

     if (got_dot) exponent--;
    }

   else if (!got_dot && *s == '.') got_dot = 1;
   else break;
  }

 if (!got_digit) goto noconv;

 *errnum = 0;
 if (*s == 'e' || *s == 'E')
  {
   save = *errnum;
   s++;
   tmpexp = my_strtol(s, &end, TRUE, errnum);
   if (*errnum == ERANGE)
    {

     if (endptr != NULL) *endptr = end;
     if (tmpexp < 0) goto underflow; else goto overflow;
    }

   else if (end == s) end = (char *) s - 1;
   errno = save;
   s = end;
   exponent += tmpexp;
  }
 if (endptr != NULL) *endptr = s;
 if (num == 0.0) return(0.0);


 if (exponent < 0)
  { if (num < MY_MINDOUBLE * pow(10.0, (double) -exponent)) goto underflow; }
 else if (exponent > 0)
  { if (num > MY_MAXDOUBLE * pow(10.0, (double) -exponent)) goto overflow; }
 num *= pow(10.0, (double) exponent);
 return(sign*num);

overflow:
 *errnum = ERANGE;
 return(sign*MY_MAXDOUBLE);

underflow:
 if (endptr != NULL) *endptr = nptr;
 *errnum = ERANGE;
 return(0.0);

noconv:
 if (endptr != NULL) *endptr = nptr;
 *errnum = EINVAL;
 return(0.0);
}
