glade_python_setup ()
{
  gchar *command;
  const gchar *module_path;

  Py_SetProgramName (PACKAGE_NAME);


  python_init ();


  PyErr_Clear ();
  glade_python_init_pygobject_check (PYGOBJECT_REQUIRED_MAJOR,
                                     PYGOBJECT_REQUIRED_MINOR,
                                     PYGOBJECT_REQUIRED_MICRO);
  if (PyErr_Occurred ())
    {
      PyObject *ptype, *pvalue, *ptraceback;
      PyErr_Fetch (&ptype, &pvalue, &ptraceback);
      g_warning ("Unable to load pygobject module >= %d.%d.%d, "
                 "please make sure it is in python's path (sys.path). "
                 "(use PYTHONPATH env variable to specify non default paths)\n%s",
                 PYGOBJECT_REQUIRED_MAJOR, PYGOBJECT_REQUIRED_MINOR,
                 PYGOBJECT_REQUIRED_MICRO, PyString_AsString (pvalue));
      PyErr_Clear ();
      Py_Finalize ();

      return TRUE;
    }

  pyg_disable_warning_redirections ();


  module_path = g_getenv (GLADE_ENV_MODULE_PATH);
  if (module_path == NULL)
    command = g_strdup_printf ("import sys; sys.path+=['%s'];\n",
                               glade_app_get_modules_dir ());
  else
    command = g_strdup_printf ("import sys; sys.path+=['%s', '%s'];\n",
                               module_path,
                               glade_app_get_modules_dir ());

  PyRun_SimpleString (command);
  g_free (command);

  return FALSE;
}
