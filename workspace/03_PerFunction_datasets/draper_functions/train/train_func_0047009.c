port_rep_from_file(scheme *sc, FILE *f, int prop) {

  port *pt;
  pt=(port*)sc->malloc(sizeof(port));
  if(pt==0) {
    return 0;
  }


  pt->kind=port_file|prop;
  pt->rep.stdio.file=f;
  pt->rep.stdio.closeit=0;
  return pt;
}
