gf_check_and_set_mem_acct (glusterfs_ctx_t *ctx, int argc, char *argv[])
{
        int i = 0;
        for (i = 0; i < argc; i++) {
                if (strcmp (argv[i], "--mem-accounting") == 0) {
			gf_mem_acct_enable_set (ctx);
                        break;
                }
        }
}
