cattle_interpreter_run (CattleInterpreter  *self,
                        GError            **error)
{
	CattleProgram *program;
	CattleInstruction *instruction;
	gboolean success = FALSE;

	g_return_val_if_fail (CATTLE_IS_INTERPRETER (self), FALSE);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);
	g_return_val_if_fail (!self->priv->disposed, FALSE);

	self->priv->stack = NULL;
	self->priv->had_input = FALSE;

	program = self->priv->program;
	instruction = cattle_program_get_instructions (program);
	self->priv->input = cattle_program_get_input (program);

	if (self->priv->input != NULL) {
		self->priv->had_input = TRUE;
	}
	self->priv->input_cursor = self->priv->input;

	success = run (self, error);

	if (self->priv->had_input == TRUE) {
		g_free (self->priv->input);
		self->priv->input = NULL;
		self->priv->input_cursor = NULL;
	}
	self->priv->had_input = FALSE;

	if (self->priv->stack != NULL) {
		g_slist_free (self->priv->stack);
	}
	self->priv->stack = NULL;

	g_object_unref (instruction);

	return success;
}
