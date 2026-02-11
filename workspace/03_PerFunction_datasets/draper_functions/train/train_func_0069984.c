atom_op_test(atom_exec_context *ctx, int *ptr, int arg)
{
	uint8_t attr = U8((*ptr)++);
	uint32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, NULL, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	ctx->ctx->cs_equal = ((dst & src) == 0);
	SDEBUG("   result: %s\n", ctx->ctx->cs_equal ? "EQ" : "NE");
}
