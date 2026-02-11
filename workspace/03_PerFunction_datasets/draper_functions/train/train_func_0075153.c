libdef_push(BuildCtx *ctx, char *p, int arg)
{
  UNUSED(arg);
  if (ctx->mode == BUILD_libdef) {
    int len = (int)strlen(p);
    if (*p == '"') {
      if (len > 1 && p[len-1] == '"') {
	p[len-1] = '\0';
	libdef_name(p+1, LIBINIT_STRING);
	return;
      }
    } else if (*p >= '0' && *p <= '9') {
      char *ep;
      double d = strtod(p, &ep);
      if (*ep == '\0') {
	if (optr+1+sizeof(double) > obuf+sizeof(obuf)) {
	  fprintf(stderr, "Error: output buffer overflow\n");
	  exit(1);
	}
	*optr++ = LIBINIT_NUMBER;
	memcpy_endian(optr, &d, sizeof(double));
	optr += sizeof(double);
	return;
      }
    } else if (!strcmp(p, "lastcl")) {
      if (optr+1 > obuf+sizeof(obuf)) {
	fprintf(stderr, "Error: output buffer overflow\n");
	exit(1);
      }
      *optr++ = LIBINIT_LASTCL;
      return;
    } else if (len > 4 && !strncmp(p, "top-", 4)) {
      if (optr+2 > obuf+sizeof(obuf)) {
	fprintf(stderr, "Error: output buffer overflow\n");
	exit(1);
      }
      *optr++ = LIBINIT_COPY;
      *optr++ = (uint8_t)atoi(p+4);
      return;
    }
    fprintf(stderr, "Error: bad value for %sPUSH(%s)\n", LIBDEF_PREFIX, p);
    exit(1);
  }
}
