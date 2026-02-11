sigar_getline_histadd(char *buf)
{
    static char *prev = 0;
    char *p = buf;
    int len;

    while (*p == ' ' || *p == '\t' || *p == '\n')
        p++;
    if (*p) {
        len = strlen(buf);
        if (strchr(p, '\n'))
            len--;
        if (prev == 0 || strlen(prev) != len ||
                            strncmp(prev, buf, len) != 0) {
            hist_buf[hist_last] = hist_save(buf);
            prev = hist_buf[hist_last];
            hist_last = (hist_last + 1) % HIST_SIZE;
            if (hist_buf[hist_last] && *hist_buf[hist_last]) {
                free(hist_buf[hist_last]);
            }
            hist_buf[hist_last] = "";


            if (gl_savehist) {
               FILE *fp;
               fp = fopen(gl_histfile, "a+");
               if (fp) {
                   fprintf(fp, "%s\n", prev);
                   gl_savehist++;
                   fclose(fp);
               }


               if (gl_savehist > HIST_SIZE) {
                  FILE *ftmp;
                  char tname[L_tmpnam];
                  char line[BUFSIZ];

                  fp = fopen(gl_histfile, "r");
                  tmpnam(tname);
                  ftmp = fopen(tname, "w");
                  if (fp && ftmp) {
                     int nline = 0;
                     while (fgets(line, BUFSIZ, fp)) {
                        nline++;
                        gl_savehist = 1;
                        if (nline > HIST_SIZE-60) {
                           gl_savehist++;
                           fprintf(ftmp, "%s", line);
                        }
                     }
                  }
                  if (fp)   fclose(fp);
                  if (ftmp) fclose(ftmp);


                  fp   = fopen(gl_histfile, "w");
                  ftmp = fopen(tname, "r");
                  if (fp && ftmp)
                     while (fgets(line, BUFSIZ, ftmp))
                        fprintf(fp, "%s", line);

                  if (fp)   fclose(fp);
                  if (ftmp) fclose(ftmp);
                  remove(tname);
               }
            }
        }
    }
    hist_pos = hist_last;
}
