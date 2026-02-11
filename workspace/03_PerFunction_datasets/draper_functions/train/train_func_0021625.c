serv_touch_idle()
{

	if (is_idle > 0) {
		LList *node;
		is_idle = 0;
		for (node = accounts; node; node = node->next) {
			if (((eb_local_account *)(node->data))->connected
				&& RUN_SERVICE(((eb_local_account *)(node->
							data)))->set_idle) {
				RUN_SERVICE(((eb_local_account *)node->data))->
					set_idle((eb_local_account *)node->data,
					0);
			}
		}
	}
	time(&lastsent);
}
