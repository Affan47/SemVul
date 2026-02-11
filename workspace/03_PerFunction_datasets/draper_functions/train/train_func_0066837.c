get_jcr_from_PyObject(PyObject *self)
{
   if (!self) {
      return NULL;
   }
   return ((JobObject *)self)->jcr;
}
