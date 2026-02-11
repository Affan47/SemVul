CopyLogFileToBackup(char *filename, char *backupname)
{
  FILE *from, *to;
    char buffer[MAX_LOG_LINE_LENGTH];

  if ((filename == NULL) || (backupname == NULL)) {
    return 1;
  }


  if ((from = fopen(filename, "r")) == NULL) {
    return 1;
  }

  if ((to = fopen(backupname, "w+")) == NULL) {
    fclose(from);
    return 1;
  }


    while (fgets(buffer, MAX_LOG_LINE_LENGTH, from)) {

    if (fputs(buffer, to) == EOF) {
      fclose(from);
      fclose(to);

      return 1;
    }
    }


    if (!feof(from)) {
    return 1;
    }


  fclose(from);
  fclose(to);

  return 0;
}
