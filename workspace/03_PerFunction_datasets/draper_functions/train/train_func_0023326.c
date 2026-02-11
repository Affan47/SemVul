maki_instance_get_dcc_send (makiInstance* inst, guint64 id)
{
	GSList* list;

	for (list = inst->dcc.list; list != NULL; list = list->next)
	{
		makiDCCSend* dcc = list->data;

		if (maki_dcc_send_id(dcc) == id)
		{
			return dcc;
		}
	}

	return NULL;
}
