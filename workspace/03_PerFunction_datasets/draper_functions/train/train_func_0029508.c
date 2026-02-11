qh_setappend(setT **setp, void *newelem) {
  int *sizep;
  void **endp;

  if (!newelem)
    return;
  if (!*setp || !*(sizep= SETsizeaddr_(*setp))) {
    qh_setlarger(setp);
    sizep= SETsizeaddr_(*setp);
  }
  *(endp= &((*setp)->e[(*sizep)++ - 1]))= newelem;
  *(++endp)= NULL;
}
