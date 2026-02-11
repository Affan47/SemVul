prealiasS(Memman *mm, Memman *mms) {

  size_t len;

  if ((char *)(mms->next_pos) - (char *)(mms->curr_pos) > 1 &&
      (((char *)(mms->curr_pos))[0] != '-' ||
       ((char *)(mms->curr_pos))[1] != '\0')) {

    if ((char *)(mm->next_pos) - (char *)(mm->curr_pos) <= 1 ||
	(((char *)(mm->curr_pos))[0] == '-' &&
	 ((char *)(mm->curr_pos))[1] == '\0')) {

      len = strlen((char *)(mms->curr_pos));
      mm->next_pos = mm->curr_pos;
      memcpy(submalloc(mm, len + 1), mms->curr_pos, len + 1);
    }
  }
  mms->next_pos = mms->curr_pos;
  return;
}
