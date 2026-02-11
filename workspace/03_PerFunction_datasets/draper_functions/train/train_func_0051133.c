gedit_spell_checker_finalize (GObject *object)
{
	GeditSpellChecker *spell_checker;

	g_return_if_fail (GEDIT_IS_SPELL_CHECKER (object));

	spell_checker = GEDIT_SPELL_CHECKER (object);

	if (spell_checker->dict != NULL)
		enchant_broker_free_dict (spell_checker->broker, spell_checker->dict);

	if (spell_checker->broker != NULL)
		enchant_broker_free (spell_checker->broker);

	G_OBJECT_CLASS (gedit_spell_checker_parent_class)->finalize (object);
}
