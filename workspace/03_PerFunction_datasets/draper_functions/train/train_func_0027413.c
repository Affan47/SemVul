save_switch (const char *opt, size_t n_args, const char *const *args,
	     bool validated)
{
  alloc_switch ();
  switches[n_switches].part1 = opt + 1;
  if (n_args == 0)
    switches[n_switches].args = 0;
  else
    {
      switches[n_switches].args = XNEWVEC (const char *, n_args + 1);
      memcpy (switches[n_switches].args, args, n_args * sizeof (const char *));
      switches[n_switches].args[n_args] = NULL;
    }

  switches[n_switches].live_cond = 0;
  switches[n_switches].validated = validated;
  switches[n_switches].ordering = 0;
  n_switches++;
}
