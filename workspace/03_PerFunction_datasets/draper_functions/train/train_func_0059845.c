get_wrapper_target_class (MonoImage *image)
{
	MonoClass *klass;


	if (image->dynamic)
		klass = ((MonoDynamicImage*)image)->wrappers_type;
	else
		klass = mono_class_get (image, mono_metadata_make_token (MONO_TABLE_TYPEDEF, 1));
	g_assert (klass);

	return klass;
}
