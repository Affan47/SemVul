job_run(PyObject *self, PyObject *arg)
{
   JCR *jcr;
   char *item;
   int stat;

   if (!PyArg_ParseTuple(arg, "s:run", &item)) {
      Dmsg0(000, "Error in ParseTuple\n");
      return NULL;
   }


   jcr = get_jcr_from_PyObject(self);
   UAContext *ua = new_ua_context(jcr);
   ua->batch = true;
   pm_strcpy(ua->cmd, item);
   parse_ua_args(ua);
   stat = run_cmd(ua, ua->cmd);
   free_ua_context(ua);

   return PyInt_FromLong((long)stat);
}
