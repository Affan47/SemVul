p_cgi_cs_init (PyObject *self, PyObject *args)
{
  CGI *cgi = ((CGIObject *) self)->cgi;
  NEOERR *err;
  CSPARSE *cs;

  if (!PyArg_ParseTuple(args, ":cs()"))
    return NULL;

  err = cgi_cs_init(cgi, &cs);
  if (err) return p_neo_error (err);
  return p_cs_to_object(cs);
}
