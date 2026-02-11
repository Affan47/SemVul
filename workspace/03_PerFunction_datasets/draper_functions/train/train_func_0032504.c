treeNeedCh (FILE *fp, int c1, char *where)
  {
    int  c2;

    if ((c2 = treeGetCh(fp)) == c1)  return TRUE;

    printf("ERROR: Expecting '%c' %s tree; found:", c1, where);
    if (c2 == EOF) {
      printf("End-of-File");
      }
    else {
      ungetc(c2, fp);
      treeEchoContext(fp, stdout, 40);
      }
    putchar('\n');
    return FALSE;
  }
