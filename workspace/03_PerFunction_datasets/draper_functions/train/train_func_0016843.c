gog_object_generate_name (GogObject *obj)
{
	GogObjectClass *klass = GOG_OBJECT_GET_CLASS (obj);
	char const *type_name;

	g_return_if_fail (klass != NULL);
	g_return_if_fail (obj->role != NULL);

	switch (obj->role->naming_conv) {
	default :
	case GOG_OBJECT_NAME_MANUALLY :
		g_warning ("Role %s should not be autogenerating names",
			   obj->role->id);

	case GOG_OBJECT_NAME_BY_ROLE :
		g_return_if_fail (obj->role != NULL);
		type_name = _(obj->role->id);
		break;

	case GOG_OBJECT_NAME_BY_TYPE :
		g_return_if_fail (klass->type_name != NULL);
		type_name = _((*klass->type_name) (obj));
		break;
	}

	if (type_name == NULL)
		type_name =  "BROKEN";

	g_free (obj->auto_name);
	obj->auto_name =  g_strdup_printf ("%s%d", type_name, obj->id);
}
