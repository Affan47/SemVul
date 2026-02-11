dyn_unload_builtin (name)
     char *name;
{
  struct builtin *b;
  void *handle;
  int ref, i;

  b = builtin_address_internal (name, 1);
  if (b == 0)
    {
      sh_notbuiltin (name);
      return (EXECUTION_FAILURE);
    }
  if (b->flags & STATIC_BUILTIN)
    {
      builtin_error (_("%s: not dynamically loaded"), name);
      return (EXECUTION_FAILURE);
    }

  handle = (void *)b->handle;
  for (ref = i = 0; i < num_shell_builtins; i++)
    {
      if (shell_builtins[i].handle == b->handle)
	ref++;
    }


  if (ref == 1 && local_dlclose (handle) != 0)
    {
      builtin_error (_("%s: cannot delete: %s"), name, dlerror ());
      return (EXECUTION_FAILURE);
    }


  delete_builtin (b);

  return (EXECUTION_SUCCESS);
}
