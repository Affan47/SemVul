main(int argc, char *argv[])
{
  if (2 == argc)
    {
      if (0 == strcmp(argv[1], "name"))
        {
          struct passwd *p;
          const char *pn = "unknown";
          p = getpwuid(getuid());
          if (p)
            pn = p->pw_name;

          fprintf(stdout, "%s\n", pn);
          return 0;
        }
      else if (0 == strcmp(argv[1], "groups"))
        {
          do_groups();
          return 0;
        }
      else if (0 == strcmp(argv[1], "foreigngroup"))
        {
          fprintf(stdout, "%ld\n", (long)foreign_group());
          return 0;
        }
      else if (0 == strcmp(argv[1], "group"))
        {
          fprintf(stdout, "%ld\n", (long)getgid());
          return 0;
        }
      else
        {
          fprintf(stderr, "%s", usage_str);
          return 1;
        }
    }
  else
    {
      fprintf(stderr, "%s", usage_str);
      return 1;
    }
}
