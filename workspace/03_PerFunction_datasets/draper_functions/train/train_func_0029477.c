xtol(aDigit)
  char  aDigit;
{
  long  digit;


  digit = -1;


  if ((aDigit >= '0') && (aDigit <= '9')) digit = (long)(aDigit - '0');
  if ((aDigit >= 'a') && (aDigit <= 'z')) digit = (long)(aDigit - 'a') + 10;
  if ((aDigit >= 'A') && (aDigit <= 'Z')) digit = (long)(aDigit - 'A') + 10;

  if (digit < 0) {
    eprinth (NULL);
    eprintf ("\n  Invalid digit \'%c\' in hexadecimal string \"%s\".\n",
             aDigit, LV_const);
    EXIT (1);
  }

  return (digit);
}
