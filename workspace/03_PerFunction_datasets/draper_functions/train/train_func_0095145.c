html_gotos(FILE *outf, Outchoices *od, choice rep) {
  extern unsigned int *rep2lng;
  extern char *anchorname[];

  choice *reporder = od->reporder;
  char **lngstr = od->lngstr;
  int i;

  fprintf(outf, "<p>(<b>%s</b>", lngstr[goto_]);
  fprintf(outf, "%s <a HREF=\"#Top\">%s</a>", lngstr[colon_], lngstr[top_]);
  for (i = 0; reporder[i] != -1; i++) {
    if (reporder[i] == rep)
      fprintf(outf, "%s %s", lngstr[colon_], lngstr[rep2lng[reporder[i]]]);
    else if (od->repq[reporder[i]])
      fprintf(outf, "%s <a HREF=\"#%s\">%s</a>", lngstr[colon_],
	      anchorname[reporder[i]], lngstr[rep2lng[reporder[i]]]);
  }
  fputs(")\n", outf);
}
