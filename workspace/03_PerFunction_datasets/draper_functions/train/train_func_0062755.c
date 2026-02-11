vault_aux_dragon(int r_idx)
{
	monster_race *r_ptr = &r_info[r_idx];
	bitflag mon_breath[RSF_SIZE];


	if (rf_has(r_ptr->flags, RF_UNIQUE)) return (FALSE);


	if (!strchr("Dd", r_ptr->d_char)) return (FALSE);


	rsf_copy(mon_breath, r_ptr->spell_flags);
	flags_mask(mon_breath, RSF_SIZE, RSF_BREATH_MASK, FLAG_END);

	if (!rsf_is_equal(mon_breath, vault_aux_dragon_mask)) return (FALSE);


	return (TRUE);
}
