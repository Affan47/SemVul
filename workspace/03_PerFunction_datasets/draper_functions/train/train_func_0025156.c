free_seq(int seq_no)
{
  int i = 1;
  int slot_index = -1;
  while (i < MAX_FRAMES_PER_ABUSED_SEQUENCE+1
	 && (slot_index = seq[seq_no].frame[i]) != 0)
    {
      SDL_FreeSurface(GFX_k[slot_index].k);
      GFX_k[slot_index].k = NULL;
      i++;
    }

  if (i == MAX_FRAMES_PER_ABUSED_SEQUENCE+1)
    log_error("Invalid sequence %d, just avoided a buffer overflow\n", seq_no);
}
