xvip_graph_cleanup(struct xvip_composite_device *xdev)
{
	struct xvip_graph_entity *entityp;
	struct xvip_graph_entity *entity;
	struct xvip_dma *dmap;
	struct xvip_dma *dma;

	v4l2_async_notifier_unregister(&xdev->notifier);

	list_for_each_entry_safe(entity, entityp, &xdev->entities, list) {
		of_node_put(entity->node);
		list_del(&entity->list);
	}

	list_for_each_entry_safe(dma, dmap, &xdev->dmas, list) {
		xvip_dma_cleanup(dma);
		list_del(&dma->list);
	}
}
