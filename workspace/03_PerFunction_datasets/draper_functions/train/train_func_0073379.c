player_can_study_msg(void)
{
	if (!player_can_cast_msg())
		return FALSE;

	if (!p_ptr->new_spells)
	{
		const char *p = ((p_ptr->class->spell_book == TV_MAGIC_BOOK) ? "spell" : "prayer");
		msg("You cannot learn any new %ss!", p);
		return FALSE;
	}

	return TRUE;
}
