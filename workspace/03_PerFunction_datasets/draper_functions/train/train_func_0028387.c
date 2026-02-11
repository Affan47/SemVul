gst_zlibError (OOP oop)
{
  zlib_stream zs = (zlib_stream) OOP_TO_OBJ (oop);
  z_stream *zlib_obj = vmProxy->OOPToCObject (zs->zlibObject);
  char *result = NULL;

  if (zlib_obj)
    {
      result = zlib_obj->msg;
      zlib_obj->msg = NULL;
    }

  return result;
}
