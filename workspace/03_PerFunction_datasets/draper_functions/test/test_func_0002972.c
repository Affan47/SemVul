e_destination_is_auto_recipient (const EDestination *dest)
{
	g_return_val_if_fail (dest && E_IS_DESTINATION (dest), FALSE);

	return dest->priv->auto_recipient;
}
