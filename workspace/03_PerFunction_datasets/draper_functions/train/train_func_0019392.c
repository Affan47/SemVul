job_does_vol_exist(PyObject *self, PyObject *args)
{
   char *VolName = NULL;

   if (!PyArg_ParseTuple(args, "s:does_volume_exist", &VolName)) {
      Dmsg0(000, "Parse tuple error in job_does_vol_exist\n");
      return NULL;
   }
   if (VolName) {
      MEDIA_DBR mr;
      int ok;
      JCR *jcr = get_jcr_from_PyObject(self);
      memset(&mr, 0, sizeof(mr));
      bstrncpy(mr.VolumeName, VolName, sizeof(mr.VolumeName));
      ok = db_get_media_record(jcr, jcr->db, &mr);
      return Py_BuildValue("i", ok);
   }
   Py_INCREF(Py_None);
   return Py_None;
}
