fz_free_link_dest(fz_context *ctx, fz_link_dest *dest)
{
	switch(dest->kind)
	{
	case FZ_LINK_NONE:
	case FZ_LINK_GOTO:
		break;
	case FZ_LINK_URI:
		fz_free(ctx, dest->ld.uri.uri);
		break;
	case FZ_LINK_LAUNCH:
		fz_free(ctx, dest->ld.launch.file_spec);
		break;
	case FZ_LINK_NAMED:
		fz_free(ctx, dest->ld.named.named);
		break;
	case FZ_LINK_GOTOR:
		fz_free(ctx, dest->ld.gotor.file_spec);
		break;
	}
}
