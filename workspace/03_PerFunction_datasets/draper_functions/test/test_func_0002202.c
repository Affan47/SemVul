scm_done_free (long size)
{
  scm_c_issue_deprecation_warning
    ("scm_done_free is deprecated.  "
     "Use scm_gc_unregister_collectable_memory instead.");

  if (size >= 0)
    scm_gc_unregister_collectable_memory (NULL, size, "foreign mallocs");
  else
    scm_gc_register_collectable_memory (NULL, -size, "foreign mallocs");
}
