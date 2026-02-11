isert_free_comps(struct isert_device *device)
{
	int i;

	for (i = 0; i < device->comps_used; i++) {
		struct isert_comp *comp = &device->comps[i];

		if (comp->cq) {
			cancel_work_sync(&comp->work);
			ib_destroy_cq(comp->cq);
		}
	}
	kfree(device->comps);
}
