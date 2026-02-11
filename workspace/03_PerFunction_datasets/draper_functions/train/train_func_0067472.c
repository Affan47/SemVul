gda_holder_set_value_str (GdaHolder *holder, GdaDataHandler *dh, const gchar *value, GError **error)
{
	g_return_val_if_fail (GDA_IS_HOLDER (holder), FALSE);
	g_return_val_if_fail (holder->priv, FALSE);
	g_return_val_if_fail (!dh || GDA_IS_DATA_HANDLER (dh), FALSE);

	if (!value || !g_ascii_strcasecmp (value, "NULL"))
                return gda_holder_set_value (holder, NULL, error);
	else {
		GValue *gdaval = NULL;
		gboolean retval = FALSE;

		gda_holder_lock ((GdaLockable*) holder);
		if (!dh)
			dh = gda_data_handler_get_default (holder->priv->g_type);
		if (dh)
			gdaval = gda_data_handler_get_value_from_str (dh, value, holder->priv->g_type);

		if (gdaval)
			retval = real_gda_holder_set_value (holder, gdaval, FALSE, error);
		else
			g_set_error (error, GDA_HOLDER_ERROR, GDA_HOLDER_STRING_CONVERSION_ERROR,
				     _("Unable to convert string to '%s' type"),
				     gda_g_type_to_string (holder->priv->g_type));
		gda_holder_unlock ((GdaLockable*) holder);
		return retval;
	}
}
