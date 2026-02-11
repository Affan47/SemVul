nv10_emit_light_model(struct gl_context *ctx, int emit)
{
	struct nouveau_pushbuf *push = context_push(ctx);
	struct gl_lightmodel *m = &ctx->Light.Model;

	BEGIN_NV04(push, NV10_3D(SEPARATE_SPECULAR_ENABLE), 1);
	PUSH_DATAb(push, m->ColorControl == GL_SEPARATE_SPECULAR_COLOR);

	BEGIN_NV04(push, NV10_3D(LIGHT_MODEL), 1);
	PUSH_DATA (push, ((m->LocalViewer ?
			 NV10_3D_LIGHT_MODEL_LOCAL_VIEWER : 0) |
			(_mesa_need_secondary_color(ctx) ?
			 NV10_3D_LIGHT_MODEL_SEPARATE_SPECULAR : 0) |
			(!ctx->Light.Enabled && ctx->Fog.ColorSumEnabled ?
			 NV10_3D_LIGHT_MODEL_VERTEX_SPECULAR : 0)));
}
