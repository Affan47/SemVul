_fd_lk_delete_unlck_locks (fd_lk_ctx_t *lk_ctx)
{
        int32_t            ret   = -1;
        fd_lk_ctx_node_t  *tmp   = NULL;
        fd_lk_ctx_node_t  *lk    = NULL;

        GF_VALIDATE_OR_GOTO ("fd-lk", lk_ctx, out);

        list_for_each_entry_safe (lk, tmp, &lk_ctx->lk_list, next) {
                if (lk->fl_type == F_UNLCK) {
                        _fd_lk_delete_lock (lk);
                        _fd_lk_destroy_lock (lk);
                }
        }
out:
        return ret;
}
