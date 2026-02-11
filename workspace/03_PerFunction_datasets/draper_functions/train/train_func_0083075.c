listEnvironment(void)
  {
    int                 i;
    extern char**       environ;

    TRACE(99, "listEnvironment()", NULL);

    printf("Environment:\n");

    if (!environ)
      {
        printf("No environment found.\n");
        return;
      }

    for (i = 0; environ[i] && environ[i]; i++)
      { printf("%s\n", environ[i]); }
  }
