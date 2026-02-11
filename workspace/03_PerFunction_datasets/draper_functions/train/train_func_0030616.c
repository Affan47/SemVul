scm_c_hook_run (scm_t_c_hook *hook, void *data)
{
  scm_t_c_hook_entry *entry = hook->first;
  scm_t_c_hook_type type = hook->type;
  void *res = 0;
  while (entry)
    {
      res = (entry->func) (hook->data, entry->data, data);
      if (res)
	{
	  if (type == SCM_C_HOOK_OR)
	    break;
	}
      else
	{
	  if (type == SCM_C_HOOK_AND)
	    break;
	}
      entry = entry->next;
    }
  return res;
}
