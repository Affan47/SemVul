redirect_jump (rtx jump, rtx nlabel, int delete_unused)
{
  rtx olabel = JUMP_LABEL (jump);

  if (nlabel == olabel)
    return 1;

  if (! redirect_jump_1 (jump, nlabel) || ! apply_change_group ())
    return 0;

  redirect_jump_2 (jump, olabel, nlabel, delete_unused, 0);
  return 1;
}
