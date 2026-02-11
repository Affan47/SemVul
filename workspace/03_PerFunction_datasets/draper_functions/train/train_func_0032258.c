h_svc_server_introduced(hook_data_client *hdata)
{
	rb_dlink_node *ptr;

	RB_DLINK_FOREACH(ptr, service_list.head)
	{
		if(!irccmp((const char *) ptr->data, hdata->target->name))
		{
			hdata->target->flags |= FLAGS_SERVICE;
			return;
		}
	}
}
