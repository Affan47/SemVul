ipmipower_connection_clear (struct ipmipower_connection *ic)
{
  assert (ic);

  _clean_fd (ic->ipmi_fd);
  if (cbuf_drop (ic->ipmi_in, -1) < 0)
    {
      IPMIPOWER_ERROR (("cbuf_drop: %s", strerror (errno)));
      exit (1);
    }
  if (cbuf_drop (ic->ipmi_out, -1) < 0)
    {
      IPMIPOWER_ERROR (("cbuf_drop: %s", strerror (errno)));
      exit (1);
    }
  return;
}
