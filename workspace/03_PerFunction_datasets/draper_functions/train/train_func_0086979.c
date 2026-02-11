confirm_change_group (void)
{
  int i;
  rtx last_object = NULL;

  for (i = 0; i < num_changes; i++)
    {
      rtx object = changes[i].object;

      if (changes[i].unshare)
	*changes[i].loc = copy_rtx (*changes[i].loc);


      if (object)
	{
	  if (object != last_object && last_object && INSN_P (last_object))
	    df_insn_rescan (last_object);
	  last_object = object;
	}
    }

  if (last_object && INSN_P (last_object))
    df_insn_rescan (last_object);
  num_changes = 0;
}
