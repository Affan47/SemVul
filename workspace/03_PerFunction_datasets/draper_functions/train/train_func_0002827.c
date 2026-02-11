mono_type_get_full (MonoImage *image, guint32 type_token, MonoGenericContext *context)
{
	MonoError error;
	MonoType *type = NULL;
	gboolean inflated = FALSE;


	if (image->dynamic)
		return mono_class_get_type (mono_lookup_dynamic_token (image, type_token, context));

	if ((type_token & 0xff000000) != MONO_TOKEN_TYPE_SPEC) {
		MonoClass *class = mono_class_get_full (image, type_token, context);
		return class ? mono_class_get_type (class) : NULL;
	}

	type = mono_type_retrieve_from_typespec (image, type_token, context, &inflated, &error);

	if (!mono_error_ok (&error)) {

		char *name = mono_class_name_from_token (image, type_token);
		char *assembly = mono_assembly_name_from_token (image, type_token);

		g_warning ("Error loading type %s from %s due to %s", name, assembly, mono_error_get_message (&error));

		mono_error_cleanup (&error);
		mono_loader_set_error_type_load (name, assembly);
		return NULL;
	}

	if (inflated) {
		MonoType *tmp = type;
		type = mono_class_get_type (mono_class_from_mono_type (type));


		if (type->type != tmp->type)
			type = tmp;
		else
			mono_metadata_free_type (tmp);
	}
	return type;
}
