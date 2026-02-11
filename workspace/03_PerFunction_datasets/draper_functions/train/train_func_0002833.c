xml_write_liquescentia (FILE * f, char liquescentia)
{
  if (liquescentia == L_NO_LIQUESCENTIA)
    {
      return;
    }
  if (is_initio_debilis (liquescentia))
    {
      fprintf (f, "<initio_debilis />");
    }
  if (liquescentia == L_DEMINUTUS
      || liquescentia == L_DEMINUTUS_INITIO_DEBILIS)
    {
      fprintf (f, "<figura>deminutus</figura>");
    }
  if (liquescentia == L_AUCTUS_ASCENDENS
      || liquescentia == L_AUCTUS_ASCENDENS_INITIO_DEBILIS)
    {
      fprintf (f, "<figura>auctus-ascendens</figura>");
    }
  if (liquescentia == L_AUCTUS_DESCENDENS
      || liquescentia == L_AUCTUS_DESCENDENS_INITIO_DEBILIS)
    {
      fprintf (f, "<figura>auctus-descendens</figura>");
    }
  if (liquescentia == L_AUCTA || liquescentia == L_AUCTA_INITIO_DEBILIS)
    {
      fprintf (f, "<figura>auctus</figura>");
    }
}
