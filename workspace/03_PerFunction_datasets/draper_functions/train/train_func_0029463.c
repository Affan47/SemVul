send_gamma_tables (NEC_Scanner *s)
{
  if (s->dev->sensedat.model == PCIN500)
    {
      return send_binary_gamma_tables(s);
    }
  else
    {
      return send_ascii_gamma_tables(s);
    }

}
