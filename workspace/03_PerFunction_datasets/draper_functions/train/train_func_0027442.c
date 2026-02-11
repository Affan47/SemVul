return_first_matching (GckObject *object, gpointer user_data)
{
	GckObject **result = (GckObject**)user_data;

	g_return_val_if_fail (GCK_IS_OBJECT (object), FALSE);
	g_return_val_if_fail (result != NULL, FALSE);
	g_return_val_if_fail (*result == NULL, FALSE);
	*result = g_object_ref (object);


	return FALSE;
}
