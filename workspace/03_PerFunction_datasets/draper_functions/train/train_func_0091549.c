inchar(scheme *sc) {
  int c;
  port *pt;
 again:
  pt=sc->inport->_object._port;
  c=basic_inchar(pt);
  if(c==EOF && sc->inport==sc->loadport && sc->file_i!=0) {
    file_pop(sc);
    if(sc->nesting!=0) {
      return EOF;
    }
    goto again;
  }
  return c;
}
