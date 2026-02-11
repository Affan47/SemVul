_trig_del(void *x) {
	trig_mgr_info_t * tmp = (trig_mgr_info_t *) x;
	xfree(tmp->res_id);
	xfree(tmp->orig_res_id);
	xfree(tmp->program);
	FREE_NULL_BITMAP(tmp->nodes_bitmap);
	FREE_NULL_BITMAP(tmp->orig_bitmap);
	xfree(tmp);
}
