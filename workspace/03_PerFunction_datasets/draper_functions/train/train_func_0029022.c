ipa_reference_get_not_written_global (struct cgraph_node *fn)
{
  ipa_reference_optimization_summary_t info;

  info = get_reference_optimization_summary (fn);
  if (info)
    return info->statics_not_written;
  else if (flags_from_decl_or_type (fn->decl) & ECF_LEAF)
    return all_module_statics;
  else
    return NULL;
}
