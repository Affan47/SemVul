read_iambic_key_mouse(double ticklen)
{
  static int dah=0,dit=0;
  static struct cwirc_keyer_state is={0};

  if(sharedmem->invertpaddles)
  {
    dah=sharedmem->mouseinputbutton0;
    dit=sharedmem->mouseinputbutton1;
  }
  else
  {
    dit=sharedmem->mouseinputbutton0;
    dah=sharedmem->mouseinputbutton1;
  }

  return(cwirc_run_keyer(&is,dit,dah,sharedmem->wpm,sharedmem->iambicmode,
	sharedmem->do_midelementmodeB,sharedmem->do_ditmemory,
	sharedmem->do_dahmemory,sharedmem->do_autocharspacing,
	sharedmem->do_autowordspacing,sharedmem->dit_weight,ticklen));
}
