vault_aux_giant(int r_idx)
{
	monster_race *r_ptr = &r_info[r_idx];


	if (rf_has(r_ptr->flags, RF_UNIQUE)) return (FALSE);


	if (!strchr("P", r_ptr->d_char)) return (FALSE);


	return (TRUE);
}
