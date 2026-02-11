editor(int handle, int tag)
{
	if(!_data)
		return;

	switch(_data->type(handle))
	{
	  default:
		log_printf(ELOG, "kobo_form_t: Unknown data type!\n");
		break;
	  case CFG_BOOL:
		onoff(_data->description(handle), (int *)NULL, tag);
		current_widget->user2 = handle;
		break;
	  case CFG_INT:
	  case CFG_FLOAT:
		spin(_data->description(handle), (int *)NULL,
				-100000, 100000, "", tag);
		current_widget->user2 = handle;
		break;
	  case CFG_STRING:
		log_printf(ELOG, "kobo_form_t: String editor not yet implemented!\n");
		break;
	}
}
