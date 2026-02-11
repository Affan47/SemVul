atk_state_set_is_empty (AtkStateSet   *set)
{
  AtkRealStateSet *real_set;
  g_return_val_if_fail (ATK_IS_STATE_SET (set), FALSE);

  real_set = (AtkRealStateSet *)set;

  if (real_set->state)
    return FALSE;
  else
    return TRUE;
}
