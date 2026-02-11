sms_get_deleted(gn_data *data)
{
	int i, j, found = 0;

	for (i = 0; i < data->folder_stats[data->sms_folder->folder_id]->used; i++) {
		found = 0;

		for (j = 0; j < data->sms_folder->number; j++) {
			if (data->message_list[i][data->sms_folder->folder_id]->location == data->sms_folder->locations[j]) found = 1;
		}
		if ((found == 0) && (data->message_list[i][data->sms_folder->folder_id]->status == GN_SMS_FLD_Old)) {
			dprintf("found a deleted message!!!! i: %i, loc: %i, MT: %i \n",
					i, data->message_list[i][data->sms_folder->folder_id]->location, data->sms_folder->folder_id);

			data->message_list[i][data->sms_folder->folder_id]->status = GN_SMS_FLD_Deleted;
			data->sms_status->changed++;
			data->folder_stats[data->sms_folder->folder_id]->changed++;
		}
	}
	return GN_ERR_NONE;
}
