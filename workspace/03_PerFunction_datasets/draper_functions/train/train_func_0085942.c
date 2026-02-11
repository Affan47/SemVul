nitro_XmlReader_init ( nitro_XmlReaderObject* self, PyObject *args, PyObject *kwds ) {

  const char* filename;
  if (!PyArg_ParseTuple(args,"s",&filename)) {
     PyErr_SetString( PyExc_Exception, "XmlReader(filename)");
     return -1;
  }

  try {
  self->m_reader = new Nitro::XmlReader ( filename );
  } catch ( const Nitro::Exception &e ) {
    NITRO_EXC(e, -1);
 }

 return 0;
}
