mono_class_inflate_generic_type_with_mempool (MonoImage *image, MonoType *type, MonoGenericContext *context, MonoError *error)
{
	MonoType *inflated = NULL;
	mono_error_init (error);

	if (context)
		inflated = inflate_generic_type (image, type, context, error);
	if (!mono_error_ok (error))
		return NULL;

	if (!inflated) {
		MonoType *shared = mono_metadata_get_shared_type (type);

		if (shared) {
			return shared;
		} else {
			return mono_metadata_type_dup (image, type);
		}
	}

	mono_stats.inflated_type_count++;
	return inflated;
}
