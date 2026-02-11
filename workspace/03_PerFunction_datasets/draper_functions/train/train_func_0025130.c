swtnl_emit_attr(struct gl_context *ctx, struct tnl_attr_map *m, int attr, int emit)
{
	TNLcontext *tnl = TNL_CONTEXT(ctx);

	if (tnl->render_inputs_bitset & BITFIELD64_BIT(attr))
		*m = (struct tnl_attr_map) {
			.attrib = attr,
			.format = emit,
		};
	else
		*m = (struct tnl_attr_map) {
			.format = EMIT_PAD,
			.offset = _tnl_format_info[emit].attrsize,
		};
}
