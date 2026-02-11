unrrduUsageUnu(const char *me, hestParm *hparm) {
  char buff[AIR_STRLEN_LARGE], fmt[AIR_STRLEN_LARGE];
  unsigned int cmdi, chi, len, maxlen;

  maxlen = 0;
  for (cmdi=0; unrrduCmdList[cmdi]; cmdi++) {
    maxlen = AIR_MAX(maxlen, AIR_UINT(strlen(unrrduCmdList[cmdi]->name)));
  }

  sprintf(buff, "--- unu: Utah Nrrd Utilities command-line interface ---");
  len = AIR_UINT(strlen(buff));
  sprintf(fmt, "%%%us\n", (hparm->columns > len
                           ? hparm->columns-len
                           : 0)/2 + len - 1);
  fprintf(stdout, fmt, buff);
  for (cmdi=0; unrrduCmdList[cmdi]; cmdi++) {
    int nofft;
    if (unrrduCmdList[cmdi]->hidden) {

      continue;
    }
    nofft = !strcmp(unrrduCmdList[cmdi]->name, "fft") && !nrrdFFTWEnabled;
    len = AIR_UINT(strlen(unrrduCmdList[cmdi]->name));
    len += !!nofft;
    strcpy(buff, "");
    for (chi=len; chi<maxlen; chi++)
      strcat(buff, " ");
    if (nofft) {
      strcat(buff, "(");
    }
    strcat(buff, me);
    strcat(buff, " ");
    strcat(buff, unrrduCmdList[cmdi]->name);
    strcat(buff, " ... ");
    len = AIR_UINT(strlen(buff));
    fprintf(stdout, "%s", buff);
    if (nofft) {
      char *infop;

      fprintf(stdout, "Not Enabled: ");
      infop = AIR_CALLOC(strlen(unrrduCmdList[cmdi]->info) + 2, char);
      sprintf(infop, "%s)", unrrduCmdList[cmdi]->info);
      _hestPrintStr(stdout, len, len, hparm->columns,
                    infop, AIR_FALSE);
      free(infop);
    } else {
      _hestPrintStr(stdout, len, len, hparm->columns,
                    unrrduCmdList[cmdi]->info, AIR_FALSE);
    }
  }
  return;
}
