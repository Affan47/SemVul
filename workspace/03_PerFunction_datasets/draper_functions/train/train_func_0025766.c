gth_slideshow_preferences_get_widget (GthSlideshowPreferences *self,
				      const char              *name)
{
	if (strcmp (name, "transition_combobox") == 0)
		return self->priv->transition_combobox;
	else
		return _gtk_builder_get_widget (self->priv->builder, name);
}
