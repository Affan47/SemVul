fossil_print(const char *zFormat, ...){
  va_list ap;
  va_start(ap, zFormat);
  if( g.cgiOutput ){
    cgi_vprintf(zFormat, ap);
  }else{
    Blob b = empty_blob;
    vxprintf(&b, zFormat, ap);
    fossil_puts(blob_str(&b), 0);
    blob_reset(&b);
  }
  va_end(ap);
}
