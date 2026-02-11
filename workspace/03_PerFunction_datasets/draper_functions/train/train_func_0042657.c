_kadm5_connect(void *handle)
{
    kadm5_client_context *ctx = handle;
    if(ctx->sock == -1)
	return kadm_connect(ctx);
    return 0;
}
