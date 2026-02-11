camel_medium_add_header (CamelMedium *medium,
                         const gchar *name,
                         gconstpointer value)
{
	CamelMediumClass *class;

	g_return_if_fail (CAMEL_IS_MEDIUM (medium));
	g_return_if_fail (name != NULL);
	g_return_if_fail (value != NULL);

	class = CAMEL_MEDIUM_GET_CLASS (medium);
	g_return_if_fail (class->add_header != NULL);

	class->add_header (medium, name, value);
}
