state_base_out(struct drm_intel_decode *ctx, unsigned int index,
	       const char *name)
{
	if (ctx->data[index] & 1) {
		instr_out(ctx, index,
			  "%s state base address 0x%08x\n", name,
			  ctx->data[index] & ~1);
	} else {
		instr_out(ctx, index, "%s state base not updated\n",
			  name);
	}
}
