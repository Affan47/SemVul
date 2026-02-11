elem_delete_data(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.elem_id > 0 && sd->eld) {
		status_change_elemclear(&sd->bl);
		unit_free(&sd->eld->bl,0);
		intif_delete_elemdata(sd->status.account_id,sd->status.char_id,sd->status.elem_id);
		sd->status.elem_id = 0;
		chrif_save(sd,0);
		if(sd->state.storage_flag == 1)
			storage_storage_save(sd);
	}

	return 0;
}
