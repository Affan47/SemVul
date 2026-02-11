claws_spell_entry_check_forwards_go(ClawsSpellEntry *entry)
{
	cm_return_if_fail(CLAWS_IS_SPELL_ENTRY(entry));
	cm_return_if_fail(entry->gtkaspell != NULL);

	entry->gtkaspell->continue_check = NULL;
	claws_spell_entry_context_set(entry);
	gtkaspell_check_next_prev(entry->gtkaspell, TRUE);
}
