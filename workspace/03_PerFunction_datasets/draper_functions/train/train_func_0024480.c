find_dvb_adapter(adapter **a)
{
	int na = 0;
	char buf[100];
	int fd;
	int i = 0, j = 0;
	adapter *ad;

	for (i = 0; i < MAX_ADAPTERS; i++)
		for (j = 0; j < MAX_ADAPTERS; j++)
		{
			sprintf(buf, "/dev/dvb/adapter%d/frontend%d", i, j);
			fd = open(buf, O_RDONLY | O_NONBLOCK);
			if (fd < 0)
			{
				sprintf(buf, "/dev/dvb/adapter%d/ca%d", i, j);
				fd = open(buf, O_RDONLY | O_NONBLOCK);
			}

			if (fd >= 0)
			{


				if (!a[na])
					a[na] = adapter_alloc();

				ad = a[na];
				ad->pa = i;
				ad->fn = j;

				ad->open = (Open_device) dvb_open_device;
				ad->set_pid = (Set_pid) dvb_set_pid;
				ad->del_filters = (Del_filters) dvb_del_filters;
				ad->commit = (Adapter_commit) dvb_commit;
				ad->tune = (Tune) dvb_tune;
				ad->delsys = (Dvb_delsys) dvb_delsys;
				ad->post_init = NULL;
				ad->close = (Adapter_commit) dvb_close;
				ad->get_signal = (Device_signal) dvb_get_signal;
				ad->type = ADAPTER_DVB;
				close(fd);
				na++;
				a_count = na;
				if (na == MAX_ADAPTERS)
					return;
			}
		}
	for (; na < MAX_ADAPTERS; na++)
		if (a[na])
			a[na]->pa = a[na]->fn = -1;
}
