gda_holder_get_value_str (GdaHolder *holder, GdaDataHandler *dh)
{
	const GValue *current_val;

	g_return_val_if_fail (GDA_IS_HOLDER (holder), NULL);
	g_return_val_if_fail (holder->priv, NULL);

	gda_holder_lock ((GdaLockable*) holder);
	current_val = gda_holder_get_value (holder);
        if (!current_val || GDA_VALUE_HOLDS_NULL (current_val)) {
		gda_holder_unlock ((GdaLockable*) holder);
                return NULL;
	}
        else {
		gchar *retval = NULL;
                if (!dh)
			dh = gda_data_handler_get_default (holder->priv->g_type);
		if (dh)
                        retval = gda_data_handler_get_str_from_value (dh, current_val);
		gda_holder_unlock ((GdaLockable*) holder);
		return retval;
        }
}
