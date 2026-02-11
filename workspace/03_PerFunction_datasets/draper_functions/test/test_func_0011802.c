tcl_md5(cd, irp, objc, objv)
ClientData cd;
Tcl_Interp *irp;
int objc;
Tcl_Obj *CONST objv[];
{
#else
static int tcl_md5 STDVAR
{
#endif
  MD5_CTX md5context;
  char digest_string[33], *string;
  unsigned char digest[16];
  int i, len;

#ifdef USE_TCL_OBJ
  if (objc != 2) {
    Tcl_WrongNumArgs(irp, 1, objv, "string");
    return TCL_ERROR;
  }
#  ifdef USE_TCL_BYTE_ARRAYS
  string = (unsigned char *)Tcl_GetByteArrayFromObj(objv[1], &len);
#  else
  string = Tcl_GetStringFromObj(objv[1], &len);
#  endif
#else
  BADARGS(2, 2, " string");

  string = argv[1];
  len = strlen(argv[1]);
#endif

  MD5_Init(&md5context);
  MD5_Update(&md5context, (unsigned char *) string, len);
  MD5_Final(digest, &md5context);
  for (i = 0; i < 16; i++)
    sprintf(digest_string + (i * 2), "%.2x", digest[i]);
  Tcl_AppendResult(irp, digest_string, NULL);
  return TCL_OK;
}
