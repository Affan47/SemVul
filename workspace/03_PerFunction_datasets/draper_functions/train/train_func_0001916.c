mono_metadata_parse_array_internal (MonoImage *m, MonoGenericContainer *container,
									gboolean transient, const char *ptr, const char **rptr)
{
	int i;
	MonoArrayType *array;
	MonoType *etype;

	array = transient ? g_malloc0 (sizeof (MonoArrayType)) : mono_image_alloc0 (m, sizeof (MonoArrayType));
	etype = mono_metadata_parse_type_full (m, container, MONO_PARSE_TYPE, 0, ptr, &ptr);
	if (!etype)
		return NULL;
	array->eklass = mono_class_from_mono_type (etype);
	array->rank = mono_metadata_decode_value (ptr, &ptr);

	array->numsizes = mono_metadata_decode_value (ptr, &ptr);
	if (array->numsizes)
		array->sizes = transient ? g_malloc0 (sizeof (int) * array->numsizes) : mono_image_alloc0 (m, sizeof (int) * array->numsizes);
	for (i = 0; i < array->numsizes; ++i)
		array->sizes [i] = mono_metadata_decode_value (ptr, &ptr);

	array->numlobounds = mono_metadata_decode_value (ptr, &ptr);
	if (array->numlobounds)
		array->lobounds = transient ? g_malloc0 (sizeof (int) * array->numlobounds) : mono_image_alloc0 (m, sizeof (int) * array->numlobounds);
	for (i = 0; i < array->numlobounds; ++i)
		array->lobounds [i] = mono_metadata_decode_signed_value (ptr, &ptr);

	if (rptr)
		*rptr = ptr;
	return array;
}
