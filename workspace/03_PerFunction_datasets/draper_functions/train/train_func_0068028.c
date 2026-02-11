textarea_attribute(
  const char *zLabel,
  int rows,
  int cols,
  const char *zVar,
  const char *zQP,
  const char *zDflt,
  int disabled
){
  const char *z = db_get(zVar, (char*)zDflt);
  const char *zQ = P(zQP);
  if( zQ && !disabled && fossil_strcmp(zQ,z)!=0){
    login_verify_csrf_secret();
    db_set(zVar, zQ, 0);
    z = zQ;
  }
  if( rows>0 && cols>0 ){
    cgi_printf("<textarea id=\"id%s\" name=\"%s\" rows=\"%d\"\n",(zQP),(zQP),(rows));
    if( disabled ){
      cgi_printf("disabled=\"disabled\"\n");
    }
    cgi_printf("cols=\"%d\">%h</textarea>\n",(cols),(z));
    if( zLabel && *zLabel ){
      cgi_printf("<span class=\"textareaLabel\">%s</span>\n",(zLabel));
    }
  }
}
