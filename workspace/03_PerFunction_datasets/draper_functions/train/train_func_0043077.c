nv10_emit_fog(struct gl_context *ctx, int emit)
{
	struct nouveau_context *nctx = to_nouveau_context(ctx);
	struct nouveau_pushbuf *push = context_push(ctx);
	struct gl_fog_attrib *f = &ctx->Fog;
	unsigned source = nctx->fallback == HWTNL ?
		f->FogCoordinateSource : GL_FOG_COORDINATE_EXT;
	float k[3];

	nv10_get_fog_coeff(ctx, k);

	BEGIN_NV04(push, NV10_3D(FOG_MODE), 4);
	PUSH_DATA (push, get_fog_mode(f->Mode));
	PUSH_DATA (push, get_fog_source(source, f->FogDistanceMode));
	PUSH_DATAb(push, f->Enabled);
	PUSH_DATA (push, pack_rgba_f(MESA_FORMAT_R8G8B8A8_UNORM, f->Color));

	BEGIN_NV04(push, NV10_3D(FOG_COEFF(0)), 3);
	PUSH_DATAp(push, k, 3);

	context_dirty(ctx, FRAG);
}
