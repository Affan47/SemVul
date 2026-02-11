domfrom(_cdomain dom, int ix) {
  while (ix > 0) {
    if (*dom == 0) throw PException("Domain label index out of bounds");
    dom += *dom + 1;
    ix--;
  }
  return (_domain) dom;
}
