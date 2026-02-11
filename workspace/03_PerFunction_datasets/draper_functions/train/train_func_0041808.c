punycode_strerror (Punycode_status rc)
{
  const char *p;

  bindtextdomain (PACKAGE, LOCALEDIR);

  switch (rc)
    {
    case PUNYCODE_SUCCESS:
      p = _("Success");
      break;

    case PUNYCODE_BAD_INPUT:
      p = _("Invalid input");
      break;

    case PUNYCODE_BIG_OUTPUT:
      p = _("Output would exceed the buffer space provided");
      break;

    case PUNYCODE_OVERFLOW:
      p = _("String size limit exceeded");
      break;

    default:
      p = _("Unknown error");
      break;
    }

  return p;
}
