mono_image_strndup (MonoImage *image, const char *data, guint len)
{
	char *res;
	if (!image)
		return g_strndup (data, len);
	res = (char *)mono_image_alloc (image, len + 1);
	memcpy (res, data, len);
	res [len] = 0;
	return res;
}
