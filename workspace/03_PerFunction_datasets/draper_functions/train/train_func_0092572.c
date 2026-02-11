gfxr_free_all_resources(gfx_driver_t *driver, gfx_resstate_t *state)
{
	struct param_struct params;
	int i;
	sbtree_t *tree = NULL;

	for (i = 0; i < GFX_RESOURCE_TYPES_NR; i++)
		if ((tree = state->resource_trees[i])) {
			params.args[0] = i;
			params.driver = driver;
			sbtree_foreach(tree, (void *) &params, gfxr_sbtree_free_func);
		}
}
