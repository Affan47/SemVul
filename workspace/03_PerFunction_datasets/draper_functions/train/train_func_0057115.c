gda_mysql_handler_boolean_accepts_g_type (G_GNUC_UNUSED GdaDataHandler *iface, GType type)
{
	g_assert (iface);
	return type == G_TYPE_BOOLEAN ? TRUE : FALSE;
}
