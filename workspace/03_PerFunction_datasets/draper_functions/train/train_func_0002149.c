python_init (void)
{
  const gchar *argv = g_get_prgname ();

  if (Py_IsInitialized ())
    return;

  Py_InitializeEx (0);

  PySys_SetArgv (1, (char **) &argv);
}
