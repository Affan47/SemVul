send_gamma_tables (SHARP_Scanner *s)
{
  if (s->dev->sensedat.model != JX250 && s->dev->sensedat.model != JX350)
    {
      return send_ascii_gamma_tables(s);
    }
  else
    {
      return send_binary_gamma_tables(s);
    }

}
