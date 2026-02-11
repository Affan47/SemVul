get_pin_number(int const_val)
{
int n,pin=-1;

  for (n = 0; n < 8; n++)
  {
    if ((const_val & (1 << n)) != 0)
    {

      if (pin != -1) { return -1; }
      pin = n;
    }
  }

  return pin;
}
