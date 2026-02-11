bdisp_hw_build_all_nodes(struct bdisp_ctx *ctx)
{
	struct bdisp_op_cfg cfg;
	unsigned int i, nid = 0;
	int src_x_offset = 0;

	for (i = 0; i < MAX_NB_NODE; i++)
		if (!ctx->node[i]) {
			dev_err(ctx->bdisp_dev->dev, "node %d is null\n", i);
			return -EINVAL;
		}


	if (bdisp_hw_get_op_cfg(ctx, &cfg))
		return -EINVAL;


	for (i = 0; i < MAX_VERTICAL_STRIDES; i++) {

		bdisp_hw_build_node(ctx, &cfg, ctx->node[nid],
				    cfg.dst_nbp == 1 ? BDISP_RGB : BDISP_Y,
				    src_x_offset);
		if (nid)
			ctx->node[nid - 1]->nip = ctx->node_paddr[nid];
		nid++;


		if (cfg.dst_nbp > 1) {
			bdisp_hw_build_node(ctx, &cfg, ctx->node[nid],
					    BDISP_CBCR, src_x_offset);
			ctx->node[nid - 1]->nip = ctx->node_paddr[nid];
			nid++;
		}


		src_x_offset += MAX_SRC_WIDTH;
		if (src_x_offset >= ctx->src.crop.width)
			break;
	}


	ctx->node[nid - 1]->nip = 0;

	return 0;
}
