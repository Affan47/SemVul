set_otype_from_name(const char *otname)
{

  static const OutputType OTS[] = {
    OTYPE_DETAILS,
    OTYPE_CANON,
    OTYPE_HUMAN,
    OTYPE_RFC1345,
    OTYPE_ICONV,
    OTYPE_CS2CS,
    OTYPE_MIME,
    OTYPE_ALIASES
  };


  static const Abbreviation OTNAMES[] =
  {
    { "aliases", OTS+7 },
    { "cstocs", OTS+4 },
    { "details", OTS },
    { "enca", OTS+1 },
    { "human-readable", OTS+2 },
    { "iconv", OTS+5 },
    { "mime", OTS+6 },
    { "rfc1345", OTS+3 },
  };

  const Abbreviation *p;

  p = expand_abbreviation(otname, OTNAMES,
                          sizeof(OTNAMES)/sizeof(Abbreviation),
                          "output type");
  if (p != NULL)
    options.output_type = *(OutputType*)p->data;
}
