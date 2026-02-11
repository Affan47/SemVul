update_pzl_hw_view(struct whc *whc)
{
	struct whc_qset *qset, *t;
	int period;
	u64 tmp_qh = 0;

	for (period = 0; period < 5; period++) {
		list_for_each_entry_safe(qset, t, &whc->periodic_list[period], list_node) {
			whc_qset_set_link_ptr(&qset->qh.link, tmp_qh);
			tmp_qh = qset->qset_dma;
			qset->in_hw_list = true;
		}
		update_pzl_pointers(whc, period, tmp_qh);
	}
}
