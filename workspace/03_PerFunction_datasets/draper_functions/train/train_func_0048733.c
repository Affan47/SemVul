GRSTgaclCredPrint(GRSTgaclCred *cred, FILE *fp)


{
  char *q;

  if ((cred->auri != NULL) && (cred->auri[0] != '\0'))
    {
      fprintf(fp, "<cred>\n<auri>");

      for (q=cred->auri; *q != '\0'; ++q)
              if      (*q == '<')  fputs("&lt;",   fp);
              else if (*q == '>')  fputs("&gt;",   fp);
              else if (*q == '&')  fputs("&amp;" , fp);
              else if (*q == '\'') fputs("&apos;", fp);
              else if (*q == '"')  fputs("&quot;", fp);
              else                 fputc(*q, fp);

      fprintf(fp, "</auri>\n");

      if (cred->nist_loa > 0)
            fprintf(fp, "<nist-loa>%d</nist-loa>\n", cred->nist_loa);

      if (cred->delegation > 0)
            fprintf(fp, "<delegation>%d</delegation>\n", cred->delegation);

      fprintf(fp, "</cred>\n");

      return 1;
    }

  return 0;
}
