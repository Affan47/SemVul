swtnl_restart(struct gl_context *ctx, int multi, unsigned vertex_size)
{
	const int tex_flags = NOUVEAU_BO_VRAM | NOUVEAU_BO_GART | NOUVEAU_BO_RD;
	struct nv04_context *nv04 = to_nv04_context(ctx);
	struct nouveau_pushbuf *push = context_push(ctx);
	struct nouveau_pushbuf_refn refs[] = {
		{ nv04->texture[0]->bo, tex_flags },
		{ nv04->texture[1]->bo, tex_flags },
	};


	if (nouveau_pushbuf_space(push, 32 + (4 * vertex_size), 4, 0) ||
	    nouveau_pushbuf_refn (push, refs, multi ? 2 : 1))
		return false;


	if (multi)
		swtnl_restart_mtri(nv04, push);
	else
		swtnl_restart_ttri(nv04, push);

	return true;
}
