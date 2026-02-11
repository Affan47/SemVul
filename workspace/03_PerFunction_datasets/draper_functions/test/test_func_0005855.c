cb_disk_extra(GtkWidget *widget, GdkEventButton *ev)
	{
	GList	*list;
	DiskMon	*disk;

	for (list = disk_mon_list; list; list = list->next)
		{
		disk = (DiskMon *) list->data;
		if (!disk->enabled || widget != disk->chart->drawing_area)
			continue;
		if (ev->button == 1 && ev->type == GDK_BUTTON_PRESS)
			{
			disk->extra_info = !disk->extra_info;
			draw_disk_chart(disk);
			gkrellm_config_modified();
			}
		else if (   ev->button == 3
				 || (ev->button == 1 && ev->type == GDK_2BUTTON_PRESS)
				)
			gkrellm_chartconfig_window_create(disk->chart);
		break;
		}
	return FALSE;
	}
