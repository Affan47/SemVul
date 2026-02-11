gap_filt_pdb_get_iterator_proc(const char *plugin_name, gint *count)
{
  char      *l_plugin_iterator;
  char      *canonical_name;

  canonical_name = gimp_canonicalize_identifier(plugin_name);


  l_plugin_iterator = g_strdup_printf("%s%s", canonical_name, GAP_ITERATOR_SUFFIX);


  if(gap_filt_pdb_procedure_available(l_plugin_iterator, GAP_PTYP_ITERATOR) < 0)
  {
     g_free(l_plugin_iterator);

     *count = 0;
     l_plugin_iterator = p_filt_pdb_get_alternative_iterator_proc(canonical_name, count);
  }
  else
  {
    *count = 1;
  }

  if(gap_debug)
  {
    printf("gap_filt_pdb_get_iterator_proc: END\n  plugin:%s\n  canonical:%s\n  iterator_proc:%s\n"
       , plugin_name
       , canonical_name
       , l_plugin_iterator
       );
  }

  g_free(canonical_name);

  return (l_plugin_iterator);
}
