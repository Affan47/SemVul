decode_generic_context (MonoAotModule *module, MonoGenericContext *ctx, guint8 *buf, guint8 **endbuf)
{
	guint8 *p = buf;
	guint8 *p2;
	int argc;

	p2 = p;
	argc = decode_value (p, &p);
	if (argc) {
		p = p2;
		ctx->class_inst = decode_generic_inst (module, p, &p);
		if (!ctx->class_inst)
			return FALSE;
	}
	p2 = p;
	argc = decode_value (p, &p);
	if (argc) {
		p = p2;
		ctx->method_inst = decode_generic_inst (module, p, &p);
		if (!ctx->method_inst)
			return FALSE;
	}

	*endbuf = p;
	return TRUE;
}
