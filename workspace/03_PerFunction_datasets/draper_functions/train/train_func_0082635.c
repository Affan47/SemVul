drm_mm_takedown(struct drm_mm * mm)
{
	WARN(!list_empty(&mm->head_node.node_list),
	     "Memory manager not clean during takedown.\n");
}
