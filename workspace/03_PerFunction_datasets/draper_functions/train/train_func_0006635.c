close_game(void)
{
  if (agx_file)
    agx_close_descr();
  else
    close_descr();
  fontcmd(1,-1);
  musiccmd(7,-1);
  close_interface();


  free_all_agtread();
  rfree(restart_state);rfree(undo_state);
  rfree(pictable);rfree(save_lnoun);
  rfree(verbptr);rfree(verbend);
  rfree(agt_counter);rfree(agt_var);
  free_creat_fix();
  flag=rrealloc(flag,sizeof(rbool));

  if (DEBUG_MEM)
    printf("\n\nAlloc:%ld  Freed:%ld  Difference:%ld\n",ralloc_cnt,
	   rfree_cnt,ralloc_cnt-rfree_cnt);
}
