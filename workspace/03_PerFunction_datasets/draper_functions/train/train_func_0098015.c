lpfc_sli4_fcf_pri_list_add(struct lpfc_hba *phba,
	uint16_t fcf_index,
	struct fcf_record *new_fcf_record)
{
	uint16_t current_fcf_pri;
	uint16_t last_index;
	struct lpfc_fcf_pri *fcf_pri;
	struct lpfc_fcf_pri *next_fcf_pri;
	struct lpfc_fcf_pri *new_fcf_pri;
	int ret;

	new_fcf_pri = &phba->fcf.fcf_pri[fcf_index];
	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
		"3059 adding idx x%x pri x%x flg x%x\n",
		fcf_index, new_fcf_record->fip_priority,
		 new_fcf_pri->fcf_rec.flag);
	spin_lock_irq(&phba->hbalock);
	if (new_fcf_pri->fcf_rec.flag & LPFC_FCF_ON_PRI_LIST)
		list_del_init(&new_fcf_pri->list);
	new_fcf_pri->fcf_rec.fcf_index = fcf_index;
	new_fcf_pri->fcf_rec.priority = new_fcf_record->fip_priority;
	if (list_empty(&phba->fcf.fcf_pri_list)) {
		list_add(&new_fcf_pri->list, &phba->fcf.fcf_pri_list);
		ret = lpfc_sli4_fcf_rr_index_set(phba,
				new_fcf_pri->fcf_rec.fcf_index);
		goto out;
	}

	last_index = find_first_bit(phba->fcf.fcf_rr_bmask,
				LPFC_SLI4_FCF_TBL_INDX_MAX);
	if (last_index >= LPFC_SLI4_FCF_TBL_INDX_MAX) {
		ret = 0;
		goto out;
	}
	current_fcf_pri = phba->fcf.fcf_pri[last_index].fcf_rec.priority;
	if (new_fcf_pri->fcf_rec.priority <=  current_fcf_pri) {
		list_add(&new_fcf_pri->list, &phba->fcf.fcf_pri_list);
		if (new_fcf_pri->fcf_rec.priority <  current_fcf_pri) {
			memset(phba->fcf.fcf_rr_bmask, 0,
				sizeof(*phba->fcf.fcf_rr_bmask));

			phba->fcf.eligible_fcf_cnt = 1;
		} else

			phba->fcf.eligible_fcf_cnt++;
		ret = lpfc_sli4_fcf_rr_index_set(phba,
				new_fcf_pri->fcf_rec.fcf_index);
		goto out;
	}

	list_for_each_entry_safe(fcf_pri, next_fcf_pri,
				&phba->fcf.fcf_pri_list, list) {
		if (new_fcf_pri->fcf_rec.priority <=
				fcf_pri->fcf_rec.priority) {
			if (fcf_pri->list.prev == &phba->fcf.fcf_pri_list)
				list_add(&new_fcf_pri->list,
						&phba->fcf.fcf_pri_list);
			else
				list_add(&new_fcf_pri->list,
					 &((struct lpfc_fcf_pri *)
					fcf_pri->list.prev)->list);
			ret = 0;
			goto out;
		} else if (fcf_pri->list.next == &phba->fcf.fcf_pri_list
			|| new_fcf_pri->fcf_rec.priority <
				next_fcf_pri->fcf_rec.priority) {
			list_add(&new_fcf_pri->list, &fcf_pri->list);
			ret = 0;
			goto out;
		}
		if (new_fcf_pri->fcf_rec.priority > fcf_pri->fcf_rec.priority)
			continue;

	}
	ret = 1;
out:

	new_fcf_pri->fcf_rec.flag = LPFC_FCF_ON_PRI_LIST;
	spin_unlock_irq(&phba->hbalock);
	return ret;
}
