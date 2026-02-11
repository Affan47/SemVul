mono_verifier_verify_cattr_content (MonoImage *image, MonoMethod *ctor, const guchar *data, guint32 size, GSList **error_list)
{
	VerifyContext ctx;

	if (!mono_verifier_is_enabled_for_image (image))
		return TRUE;

	init_verify_context (&ctx, image, error_list != NULL);
	ctx.stage = STAGE_TABLES;

	is_valid_cattr_content (&ctx, ctor, (const char*)data, size);

	return cleanup_context (&ctx, error_list);
}
