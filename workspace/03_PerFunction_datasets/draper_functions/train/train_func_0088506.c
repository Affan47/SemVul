gda_holder_take_value (GdaHolder *holder, GValue *value, GError **error)
{
	g_return_val_if_fail (GDA_IS_HOLDER (holder), FALSE);
	g_return_val_if_fail (holder->priv, FALSE);

	return real_gda_holder_set_value (holder, (GValue*) value, FALSE, error);
}
