exprtouri(const char *expr){
  const char *rp;
  rp = expr;
  if(cbstrfwimatch(expr, "urn:")) rp += 4;
  while((*rp >= 'A' && *rp <= 'Z') || (*rp >= 'a' && *rp <= 'z')){
    rp++;
  }
  if(rp > expr && rp[0] == ':' && rp[1] == '/' && rp[2] == '/') return expr;
  if(cbstrfwimatch(expr, "mailto:") && !strchr(expr, '/')) return expr;
  return pathtourl(expr);
}
