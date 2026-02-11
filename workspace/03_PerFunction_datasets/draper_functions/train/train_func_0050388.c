gnome_bg_crossfade_get_property (GObject    *object,
			     guint       property_id,
			     GValue     *value,
			     GParamSpec *pspec)
{
	GnomeBGCrossfade *fade;

	g_assert (GNOME_IS_BG_CROSSFADE (object));

	fade = GNOME_BG_CROSSFADE (object);

	switch (property_id)
	{
	case PROP_WIDTH:
		g_value_set_int (value, fade->priv->width);
		break;
	case PROP_HEIGHT:
		g_value_set_int (value, fade->priv->height);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
