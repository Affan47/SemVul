iquser (puuconf, argc, argv, pvar, pinfo)
     pointer puuconf ATTRIBUTE_UNUSED;
     int argc;
     char **argv;
     pointer pvar ATTRIBUTE_UNUSED;
     pointer pinfo ATTRIBUTE_UNUSED;
{
  if (argc > 1)
    zQuser = argv[1];
  if (argc > 2)
    zQsystem = argv[2];
  return UUCONF_CMDTABRET_KEEP;
}
