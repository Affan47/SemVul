csio_scsi_gather_active_ios(struct csio_scsim *scm,
			    struct csio_scsi_level_data *sld,
			    struct list_head *dest)
{
	struct list_head *tmp, *next;

	if (list_empty(&scm->active_q))
		return;


	if (sld->level == CSIO_LEV_ALL) {
		list_splice_tail_init(&scm->active_q, dest);
		return;
	}

	list_for_each_safe(tmp, next, &scm->active_q) {
		if (csio_scsi_match_io((struct csio_ioreq *)tmp, sld)) {
			list_del_init(tmp);
			list_add_tail(tmp, dest);
		}
	}
}
