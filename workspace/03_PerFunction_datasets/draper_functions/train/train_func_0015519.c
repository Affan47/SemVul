glfs_process_volfp (struct glfs *fs, FILE *fp)
{
	glusterfs_graph_t  *graph = NULL;
	int		    ret = -1;
	xlator_t	   *trav = NULL;
	glusterfs_ctx_t	   *ctx = NULL;

	ctx = fs->ctx;
	graph = glusterfs_graph_construct (fp);
	if (!graph) {
		gf_log ("glfs", GF_LOG_ERROR, "failed to construct the graph");
		goto out;
	}

	for (trav = graph->first; trav; trav = trav->next) {
		if (strcmp (trav->type, "mount/fuse") == 0) {
			gf_log ("glfs", GF_LOG_ERROR,
				"fuse xlator cannot be specified "
				"in volume file");
			goto out;
		}
	}

	ret = glusterfs_graph_prepare (graph, ctx);
	if (ret) {
		glusterfs_graph_destroy (graph);
		goto out;
	}

	ret = glusterfs_graph_activate (graph, ctx);

	if (ret) {
		glusterfs_graph_destroy (graph);
		goto out;
	}

	ret = 0;
out:
	if (fp)
		fclose (fp);

	if (!ctx->active) {
		ret = -1;
	}

	return ret;
}
