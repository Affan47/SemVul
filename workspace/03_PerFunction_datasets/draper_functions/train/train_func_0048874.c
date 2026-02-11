abi_font_combo_dispose (GObject *instance)
{
	AbiFontCombo *self;

	self = ABI_FONT_COMBO (instance);

	if (self->is_disposed) {
		return;
	}

	self->is_disposed = TRUE;

	g_object_unref (G_OBJECT (self->sort));
	self->sort = NULL;

	g_object_unref (G_OBJECT (self->model));
	self->model = NULL;

	G_OBJECT_CLASS (abi_font_combo_parent_class)->dispose (instance);
}
