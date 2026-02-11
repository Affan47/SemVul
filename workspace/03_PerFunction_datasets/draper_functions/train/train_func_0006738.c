count_shadow_nodes(struct shrinker *shrinker,
					struct shrink_control *sc)
{
	unsigned long shadow_nodes;
	unsigned long max_nodes;
	unsigned long pages;


	local_irq_disable();
	shadow_nodes = list_lru_shrink_count(&workingset_shadow_nodes, sc);
	local_irq_enable();

	pages = node_present_pages(sc->nid);


	max_nodes = pages >> (1 + RADIX_TREE_MAP_SHIFT - 3);

	if (shadow_nodes <= max_nodes)
		return 0;

	return shadow_nodes - max_nodes;
}
