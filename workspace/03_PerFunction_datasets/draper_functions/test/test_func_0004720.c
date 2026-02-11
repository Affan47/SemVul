prec_name (prec)
     short prec;
{
  int i;

  for (i = 0; prec_table[i].prec != (short) -1; i++)
    if (prec_table[i].prec == prec)
      break;
  return (prec_table[i].prec_name);
}
