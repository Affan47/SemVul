atk_state_set_contains_states (AtkStateSet   *set,
                               AtkStateType  *types,
                               gint          n_types)
{
  AtkRealStateSet *real_set;
  gint i;
  g_return_val_if_fail (ATK_IS_STATE_SET (set), FALSE);

  real_set = (AtkRealStateSet *)set;

  for (i = 0; i < n_types; i++)
  {
    if (!(real_set->state & ATK_STATE (types[i])))
      return FALSE;
  }
  return TRUE;
}
