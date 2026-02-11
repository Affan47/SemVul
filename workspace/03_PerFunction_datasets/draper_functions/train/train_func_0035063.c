g_mime_object_get_content_type_parameter (GMimeObject *object, const char *name)
{
	g_return_val_if_fail (GMIME_IS_OBJECT (object), NULL);
	g_return_val_if_fail (name != NULL, NULL);

	return g_mime_content_type_get_parameter (object->content_type, name);
}
