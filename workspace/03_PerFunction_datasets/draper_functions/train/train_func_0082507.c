gkrellm_disk_temperature_remove(gchar *id_name)
	{
	GList			*list;
	DiskMon			*disk;
	GkrellmPanel	*p;
	GkrellmDecal	*decal;
	gchar			*disk_name;
	gint			len;

	if ((disk_name = strrchr(id_name, '/')) != NULL)
		++disk_name;
	else
		disk_name = id_name;

	len = strlen(disk_name);
	for (list = disk_mon_list; list; list = list->next)
		{
		disk = (DiskMon *) list->data;
		if (!disk->chart)
			continue;
		if (   strncmp(disk->name, disk_name, len)
			|| (disk->name[len] != '\0' && !isdigit((unsigned char)disk->name[len]))
		   )
			continue;
		p = disk->chart->panel;
		decal = disk->temp_decal;
		if (gkrellm_is_decal_visible(decal))
			{
			gkrellm_make_decal_invisible(p, decal);
			p->label->position = disk->save_label_position;
			gkrellm_draw_panel_label(p);
			gkrellm_draw_panel_layers(p);
			}
		}
	}
