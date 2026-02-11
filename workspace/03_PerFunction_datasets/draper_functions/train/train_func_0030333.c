print_charsets(int only_builtin)
{
  size_t ncharsets, i;

  ncharsets = enca_number_of_charsets();
  for (i = 0; i < ncharsets; i++) {
    if (only_builtin && !enca_charset_has_ucs2_map(i))
      continue;

    switch (options.output_type) {
      case OTYPE_ALIASES:
      print_aliases(i);
      break;

      case OTYPE_CANON:
      case OTYPE_CONVERT:
      puts(enca_charset_name(i, ENCA_NAME_STYLE_ENCA));
      break;

      case OTYPE_HUMAN:
      case OTYPE_DETAILS:
      puts(enca_charset_name(i, ENCA_NAME_STYLE_HUMAN));
      break;

      case OTYPE_RFC1345:
      puts(enca_charset_name(i, ENCA_NAME_STYLE_RFC1345));
      break;

      case OTYPE_CS2CS:
      if (enca_charset_name(i, ENCA_NAME_STYLE_CSTOCS) != NULL)
        puts(enca_charset_name(i, ENCA_NAME_STYLE_CSTOCS));
      break;

      case OTYPE_ICONV:
      if (enca_charset_name(i, ENCA_NAME_STYLE_ICONV) != NULL)
        puts(enca_charset_name(i, ENCA_NAME_STYLE_ICONV));
      break;

      case OTYPE_MIME:
      if (enca_charset_name(i, ENCA_NAME_STYLE_MIME) != NULL)
        puts(enca_charset_name(i, ENCA_NAME_STYLE_MIME));
      break;

      default:
      abort();
      break;
    }
  }
}
