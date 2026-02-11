bdisp_hw_free_nodes(struct bdisp_ctx *ctx)
{
	if (ctx && ctx->node[0]) {
		DEFINE_DMA_ATTRS(attrs);

		dma_set_attr(DMA_ATTR_WRITE_COMBINE, &attrs);
		dma_free_attrs(ctx->bdisp_dev->dev,
			       sizeof(struct bdisp_node) * MAX_NB_NODE,
			       ctx->node[0], ctx->node_paddr[0], &attrs);
	}
}
