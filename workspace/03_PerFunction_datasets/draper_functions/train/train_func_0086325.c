on_is_built_finished (GObject *builder, IAnjutaBuilderHandle handle, GError *err, gpointer user_data)
{
	DmaStart *this = (DmaStart *)user_data;

	if (err == NULL)
	{

		load_target (this, this->build_target);
		start_target (this);
	}
	else
	{

		this->build_handle = ianjuta_builder_build (IANJUTA_BUILDER (builder), this->build_target, on_build_finished, this, NULL);
		return;
	}

	g_free (this->build_target);
	this->build_target = NULL;
}
