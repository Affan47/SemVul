gru_vma_close(struct vm_area_struct *vma)
{
	struct gru_vma_data *vdata;
	struct gru_thread_state *gts;
	struct list_head *entry, *next;

	if (!vma->vm_private_data)
		return;

	vdata = vma->vm_private_data;
	vma->vm_private_data = NULL;
	gru_dbg(grudev, "vma %p, file %p, vdata %p\n", vma, vma->vm_file,
				vdata);
	list_for_each_safe(entry, next, &vdata->vd_head) {
		gts =
		    list_entry(entry, struct gru_thread_state, ts_next);
		list_del(&gts->ts_next);
		mutex_lock(&gts->ts_ctxlock);
		if (gts->ts_gru)
			gru_unload_context(gts, 0);
		mutex_unlock(&gts->ts_ctxlock);
		gts_drop(gts);
	}
	kfree(vdata);
	STAT(vdata_free);
}
