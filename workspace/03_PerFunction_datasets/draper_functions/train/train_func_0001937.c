memory_bm_free(struct memory_bitmap *bm, int clear_nosave_free)
{
	struct mem_zone_bm_rtree *zone;

	list_for_each_entry(zone, &bm->zones, list)
		free_zone_bm_rtree(zone, clear_nosave_free);

	free_list_of_pages(bm->p_list, clear_nosave_free);

	INIT_LIST_HEAD(&bm->zones);
}
