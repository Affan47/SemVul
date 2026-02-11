real_insn_for_shadow (rtx insn)
{
  struct delay_pair *pair;

  if (delay_htab == NULL)
    return NULL_RTX;

  pair
    = (struct delay_pair *)htab_find_with_hash (delay_htab_i2, insn,
						htab_hash_pointer (insn));
  if (!pair || pair->stages > 0)
    return NULL_RTX;
  return pair->i1;
}
