scm_module_transformer (SCM module)
{
  if (scm_is_false (module))
    return SCM_BOOL_F;
  else
    return SCM_MODULE_TRANSFORMER (module);
}
