is_mirror_image_removable(struct logical_volume *mimage_lv, void *baton)
{
	struct physical_volume *pv;
	struct lv_segment *seg;
	int pv_found;
	struct pv_list *pvl;
	uint32_t s;
	struct dm_list *removable_pvs = baton;

	if (!baton || dm_list_empty(removable_pvs))
		return 1;

	dm_list_iterate_items(seg, &mimage_lv->segments) {
		for (s = 0; s < seg->area_count; s++) {
			if (seg_type(seg, s) != AREA_PV) {


				return 0;
			}

			pv = seg_pv(seg, s);

			pv_found = 0;
			dm_list_iterate_items(pvl, removable_pvs) {
				if (id_equal(&pv->id, &pvl->pv->id)) {
					pv_found = 1;
					break;
				}
				if (pvl->pv->dev && pv->dev &&
				    pv->dev->dev == pvl->pv->dev->dev) {
					pv_found = 1;
					break;
				}
			}
			if (!pv_found)
				return 0;
		}
	}

	return 1;
}
