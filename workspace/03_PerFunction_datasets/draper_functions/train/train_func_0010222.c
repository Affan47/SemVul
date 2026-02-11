printfile(char *dn, GRSTgaclPerm perm, char *help_uri, char *dir_path,
                  char *file, char *dir_uri, char *admin_file)
{
  int   c;
  char *dir_path_file;
  FILE *fp;
  struct stat statbuf;

  if (!GRSTgaclPermHasRead(perm)) GRSThttpError("403 Forbidden");

  if (file[0] == '\0') GRSThttpError("403 Forbidden");

  dir_path_file = malloc(strlen(dir_path) + strlen(file) + 2);

  strcpy(dir_path_file, dir_path);
  strcat(dir_path_file, "/");
  strcat(dir_path_file, file);

  if ((stat(dir_path_file, &statbuf) != 0) ||
        !S_ISREG(statbuf.st_mode)) GRSThttpError("403 Forbidden");

  fp = fopen(dir_path_file, "r");
  if (fp == NULL) GRSThttpError("500 Internal server error");

  printf("Status: 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n",
         statbuf.st_size);

  while ((c = fgetc(fp)) != EOF) putchar(c);

  fflush(stdout);
  fclose(fp);
}
