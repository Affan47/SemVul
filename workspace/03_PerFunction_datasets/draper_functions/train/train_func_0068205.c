veclinear_emit(struct gl_context *ctx, struct radeon_state_atom *atom)
{
   r200ContextPtr r200 = R200_CONTEXT(ctx);
   BATCH_LOCALS(&r200->radeon);
   uint32_t dwords = atom->check(ctx, atom);

   OUT_VECLINEAR(atom->cmd[0], atom->cmd+1);
}
