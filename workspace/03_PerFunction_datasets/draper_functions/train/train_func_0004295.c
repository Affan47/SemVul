fr_command_unstuff_finalize (GObject *object)
{
	FrCommandUnstuff *self;

	g_return_if_fail (object != NULL);
	g_return_if_fail (FR_IS_COMMAND_UNSTUFF (object));

	self = FR_COMMAND_UNSTUFF (object);

	if (self->target_dir != NULL) {
		recursive_rmdir (self->target_dir);
		g_free (self->target_dir);
	}

	if (G_OBJECT_CLASS (fr_command_unstuff_parent_class)->finalize)
		G_OBJECT_CLASS (fr_command_unstuff_parent_class)->finalize (object);
}
