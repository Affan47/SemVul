op_aread(void)
{
  int maxlen, length, initlen;
  unsigned char term;
  zword text = operand[0];

  maxlen = LOBYTE(text);
  initlen = LOBYTE(text + 1);
  if(numoperands < 3)
    operand[2] = 0;
  if(numoperands < 4)
    operand[3] = 0;

  length = n_read(text + 2, maxlen, operand[1], initlen,
		operand[2], operand[3], &term);
  if(!read_abort) {
    LOBYTEwrite(text + 1, length);
    mop_store_result(term);

    if(allow_saveundo) {
      if(!has_done_save_undo && auto_save_undo)
        saveundo(FALSE);
      has_done_save_undo = FALSE;
    }
  }
}
