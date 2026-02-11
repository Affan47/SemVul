pkg_getOptionsFromICUConfig(UBool verbose, UOption *option) {
#if U_HAVE_POPEN
    FILE *p = NULL;
    size_t n;
    static char buf[512] = "";
    char cmdBuf[1024];
    UErrorCode status = U_ZERO_ERROR;
    const char cmd[] = "icu-config --incpkgdatafile";


    findDirname(progname, cmdBuf, 1024, &status);
    if(U_SUCCESS(status)) {
      if (cmdBuf[0] != 0) {
          uprv_strncat(cmdBuf, U_FILE_SEP_STRING, 1024);
      }
      uprv_strncat(cmdBuf, cmd, 1023);

      if(verbose) {
        fprintf(stdout, "# Calling icu-config: %s\n", cmdBuf);
      }
      p = popen(cmdBuf, "r");
    }

    if(p == NULL || (n = fread(buf, 1, 511, p)) <= 0) {
      if(verbose) {
        fprintf(stdout, "# Calling icu-config: %s\n", cmd);
      }
      pclose(p);

      p = popen(cmd, "r");
      if(p == NULL || (n = fread(buf, 1, 511, p)) <= 0) {
          fprintf(stderr, "%s: icu-config: No icu-config found. (fix PATH or use -O option)\n", progname);
          return -1;
      }
    }

    pclose(p);

    for (int32_t length = strlen(buf) - 1; length >= 0; length--) {
        if (buf[length] == '\n' || buf[length] == ' ') {
            buf[length] = 0;
        } else {
            break;
        }
    }

    if(buf[strlen(buf)-1]=='\n')
    {
        buf[strlen(buf)-1]=0;
    }

    if(buf[0] == 0)
    {
        fprintf(stderr, "%s: icu-config: invalid response from icu-config (fix PATH or use -O option)\n", progname);
        return -1;
    }

    if(verbose) {
      fprintf(stdout, "# icu-config said: %s\n", buf);
    }

    option->value = buf;
    option->doesOccur = TRUE;

    return 0;
#else
    return -1;
#endif
}
