qr_fd_ctx_free (qr_fd_ctx_t *qr_fd_ctx)
{
        GF_VALIDATE_OR_GOTO ("quick-read", qr_fd_ctx, out);

        GF_ASSERT (list_empty (&qr_fd_ctx->waiting_ops));

        GF_FREE (qr_fd_ctx->path);
        GF_FREE (qr_fd_ctx);

out:
        return;
}
