gegl_module_set_load_inhibit (GeglModule *module,
                              gboolean    load_inhibit)
{
  g_return_if_fail (GEGL_IS_MODULE (module));

  if (load_inhibit != module->load_inhibit)
    {
      module->load_inhibit = load_inhibit ? TRUE : FALSE;

      gegl_module_modified (module);
    }
}
