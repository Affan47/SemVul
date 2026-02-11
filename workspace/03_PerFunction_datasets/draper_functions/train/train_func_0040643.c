getlocus(system_, LINK)
long system_;
struct LOC_readloci *LINK;
{
  struct LOC_getlocus V;
  locusvalues *WITH;


  V.LINK = LINK;
  V.system = system_;
  thislocus[V.system - 1] = (locusvalues *)Malloc(sizeof(locusvalues));

  if (thislocus[V.system - 1] == NULL)
    malloc_err("locus");
  WITH = thislocus[V.system - 1];
  fscanf(datafile, "%ld%ld", &LINK->whichtype, &WITH->nallele);
  WITH->maxallele = WITH->nallele;
#if LOOPSPEED
  WITH->fgeno = (WITH->nallele * (WITH->nallele + 1) / 2);
  if (sexlink)
    WITH->mgeno = WITH->nallele;
  else
    WITH->mgeno = WITH->fgeno;
#endif
  switch (LINK->whichtype) {

  case 0:
    WITH->which = quantitative;
    break;

  case 1:
    WITH->which = affection;
    break;

  case 2:
    WITH->which = binary_;
    WITH->UU.U2.format = binformat;
    break;

  case 3:
    WITH->which = binary_;
    WITH->UU.U2.format = allformat;
    break;
  }
  if (!disequi) {
    fscanf(datafile, "%*[^\n]");
    fscanf(datafile, "%lf", &thislocus[V.system - 1]->onefreq);
  }
  else {
  fscanf(datafile, "%*[^\n]");
  getc(datafile);
  }
  if (!disequi) {
    fscanf(datafile, "%*[^\n]");
    getc(datafile);
  }
  if (disfreqs && (binary_==WITH->which)) {
    fscanf(datafile, "%*[^\n]");
    getc(datafile);
  }

  switch (WITH->which) {

  case quantitative:
    getquan(&thislocus[V.system - 1], &V);
    break;

  case affection:
    getpen(&thislocus[V.system - 1], &V);
    break;

  case binary_:
    if (WITH->UU.U2.format == binformat)
      getbin(&thislocus[V.system - 1], &V);
    else
      getnumber(&thislocus[V.system - 1], &V);
    break;
  }
  if (risk && V.system == risksys) {
    fscanf(datafile, "%*[^\n]");
    getc(datafile);
  }
}
