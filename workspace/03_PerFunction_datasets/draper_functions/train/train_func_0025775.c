get_bothtypes(dxml_element *b, int inlinetype )
{
  if (!strcasecmp("screen", b->element_name))
    {
      if (!inlinetype)
	puts("\n\n\n\n");
      puts("{\\tt %\n");
      get_paratype(b->child, 1);
      puts("}");
      if (!inlinetype)
	puts("\n\n\n\n");
    }
  else
    return 0;
  return 1;
}
