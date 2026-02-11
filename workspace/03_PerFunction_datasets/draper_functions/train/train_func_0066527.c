cli_ac_init(struct cli_matcher *root, uint8_t mindepth, uint8_t maxdepth, uint8_t dconf_prefiltering)
{
#ifdef USE_MPOOL
    assert(root->mempool && "mempool must be initialized");
#endif

    root->ac_root = (struct cli_ac_node *) mpool_calloc(root->mempool, 1, sizeof(struct cli_ac_node));
    if(!root->ac_root) {
	cli_errmsg("cli_ac_init: Can't allocate memory for ac_root\n");
	return CL_EMEM;
    }

    root->ac_root->trans = (struct cli_ac_node **) mpool_calloc(root->mempool, 256, sizeof(struct cli_ac_node *));
    if(!root->ac_root->trans) {
	cli_errmsg("cli_ac_init: Can't allocate memory for ac_root->trans\n");
	mpool_free(root->mempool, root->ac_root);
	return CL_EMEM;
    }

    root->ac_mindepth = mindepth;
    root->ac_maxdepth = maxdepth;

    if (cli_mtargets[root->type].enable_prefiltering && dconf_prefiltering) {
	root->filter = mpool_malloc(root->mempool, sizeof(*root->filter));
	if (!root->filter) {
	    cli_errmsg("cli_ac_init: Can't allocate memory for ac_root->filter\n");
	    mpool_free(root->mempool, root->ac_root->trans);
	    mpool_free(root->mempool, root->ac_root);
	    return CL_EMEM;
	}
	filter_init(root->filter);
    }

    return CL_SUCCESS;
}
