ASM_FINALLY(CTX ctx)
{
	if(IS_NOTNULL(DP(ctx->gma)->finallyStmt)) {
		BLOCK_asm(ctx, DP(ctx->gma)->finallyStmt);
	}
}
