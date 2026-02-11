mono_reflection_initialize_generic_parameter (MonoReflectionGenericParam *gparam)
{
	MonoGenericParamFull *param;
	MonoImage *image;
	MonoClass *pklass;
	MonoError error;

	image = &gparam->tbuilder->module->dynamic_image->image;

	param = mono_image_new0 (image, MonoGenericParamFull, 1);

	param->info.name = mono_string_to_utf8_image (image, gparam->name, &error);
	g_assert (mono_error_ok (&error));
	param->param.num = gparam->index;

	if (gparam->mbuilder) {
		if (!gparam->mbuilder->generic_container) {
			MonoReflectionTypeBuilder *tb = (MonoReflectionTypeBuilder *)gparam->mbuilder->type;
			MonoClass *klass = mono_class_from_mono_type (mono_reflection_type_get_handle ((MonoReflectionType*)tb));
			gparam->mbuilder->generic_container = (MonoGenericContainer *)mono_image_alloc0 (klass->image, sizeof (MonoGenericContainer));
			gparam->mbuilder->generic_container->is_method = TRUE;


			gparam->mbuilder->generic_container->is_anonymous = TRUE;
			gparam->mbuilder->generic_container->owner.image = klass->image;
		}
		param->param.owner = gparam->mbuilder->generic_container;
	} else if (gparam->tbuilder) {
		if (!gparam->tbuilder->generic_container) {
			MonoClass *klass = mono_class_from_mono_type (mono_reflection_type_get_handle ((MonoReflectionType*)gparam->tbuilder));
			gparam->tbuilder->generic_container = (MonoGenericContainer *)mono_image_alloc0 (klass->image, sizeof (MonoGenericContainer));
			gparam->tbuilder->generic_container->owner.klass = klass;
		}
		param->param.owner = gparam->tbuilder->generic_container;
	}

	pklass = mono_class_from_generic_parameter_internal ((MonoGenericParam *) param);

	gparam->type.type = &pklass->byval_arg;

	mono_class_set_ref_info (pklass, gparam);
	mono_image_append_class_to_reflection_info_set (pklass);
}
