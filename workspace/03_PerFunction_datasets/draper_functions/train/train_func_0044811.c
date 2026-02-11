loop_optimize (rtx f, FILE *dumpfile, int flags)
{
  rtx insn;
  int i;
  struct loops loops_data;
  struct loops *loops = &loops_data;
  struct loop_info *loops_info;

  loop_dump_stream = dumpfile;

  init_recog_no_volatile ();

  max_reg_before_loop = max_reg_num ();
  loop_max_reg = max_reg_before_loop;

  regs_may_share = 0;


  max_loop_num = 0;
  for (insn = f; insn; insn = NEXT_INSN (insn))
    {
      if (GET_CODE (insn) == NOTE
	  && NOTE_LINE_NUMBER (insn) == NOTE_INSN_LOOP_BEG)
	max_loop_num++;
    }


  if (max_loop_num == 0)
    return;

  loops->num = max_loop_num;


  max_uid_for_loop = get_max_uid () + 1 + max_loop_num * 32;

  uid_luid = xcalloc (max_uid_for_loop, sizeof (int));
  uid_loop = xcalloc (max_uid_for_loop, sizeof (struct loop *));


  loops->array = xcalloc (loops->num, sizeof (struct loop));


  find_and_verify_loops (f, loops);


  loops_info = xcalloc (loops->num, sizeof (struct loop_info));
  for (i = 0; i < (int) loops->num; i++)
    loops->array[i].aux = loops_info + i;


  reg_scan (f, max_reg_before_loop, 1);


  init_alias_analysis ();


  if (get_max_uid () > max_uid_for_loop)
    abort ();

  max_uid_for_loop = get_max_uid ();


  compute_luids (f, NULL_RTX, 0);


  for (i = 0; i < max_uid_for_loop; i++)
    {
      uid_luid[0] = uid_luid[i];
      if (uid_luid[0] != 0)
	break;
    }
  for (i = 0; i < max_uid_for_loop; i++)
    if (uid_luid[i] == 0)
      uid_luid[i] = uid_luid[i - 1];


  indirect_jump_in_function = indirect_jump_in_function_p (f);


  for (i = max_loop_num - 1; i >= 0; i--)
    {
      struct loop *loop = &loops->array[i];

      if (! loop->invalid && loop->end)
	{
	  scan_loop (loop, flags);
	  ggc_collect ();
	}
    }

  end_alias_analysis ();


  for (i = 0; i < (int) loops->num; i++)
    free (loops_info[i].mems);

  free (uid_luid);
  free (uid_loop);
  free (loops_info);
  free (loops->array);
}
