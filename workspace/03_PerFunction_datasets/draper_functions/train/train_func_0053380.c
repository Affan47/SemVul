glade_abort_if_derived_adaptors_exist (GType type)
{
  if (adaptor_hash)
    {
      GType retval = type;

      g_hash_table_find (adaptor_hash, glade_widget_adaptor_hash_find, &retval);
      if (retval != type)
        g_error (_("A derived adaptor (%s) of %s already exist!"),
                 g_type_name (retval), g_type_name (type));
    }
}
