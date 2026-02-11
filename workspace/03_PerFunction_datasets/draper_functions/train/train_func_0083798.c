read_nis_obj (const char *name, iofct_t readfct, freefct_t freefct,
	      size_t objsize)
{
  FILE *in = fopen (name, "rce");
  if (in == NULL)
    return NULL;

  void *obj = calloc (1, objsize);

  if (obj != NULL)
    {
      XDR xdrs;
      xdrstdio_create (&xdrs, in, XDR_DECODE);
      bool_t status = readfct (&xdrs, obj);
      xdr_destroy (&xdrs);

      if (!status)
	{
	  freefct (obj);
	  obj = NULL;
	}
    }

  fclose (in);

  return obj;
}
