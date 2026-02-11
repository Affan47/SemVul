msp430_set_status (int r, char b, char *c)
{
  int tmp = b ? (r & 0xff) : (r & 0xffff);


  if (*c == 'x')
    {
      if (!tmp)
	SET_Z;
      else
	CLR_Z;
    }
  else if (*c == '0')
    {
      CLR_Z;
    }
  else if (*c == '1')
    {
      SET_Z;
    }

  c++;

  if (*c == 'x')
    {
      if (tmp & (b ? 0x80 : 0x8000))
	SET_N;
      else
	CLR_N;
    }
  else if (*c == '0')
    {
      CLR_N;
    }
  else if (*c == '1')
    {
      SET_N;
    }

  c++;

  if (*c == 'x')
    {
      if (r < 0)
	SET_C;
      else if (b && (r & 0xffffff00ul))
	SET_C;
      else if (!b && (r & 0xffff0000ul))
	SET_C;
      else
	CLR_C;
    }
  else if (*c == '0')
    {
      CLR_C;
    }
  else if (*c == '1')
    {
      SET_C;
    }

  c++;

  if (*c == '0')
    {
      CLR_V;
    }
  else if (*c == '1')
    {
      SET_V;
    }


  if (sr & 0x00f0)
    {
      alu.signal = SIGQUIT;
    }
}
