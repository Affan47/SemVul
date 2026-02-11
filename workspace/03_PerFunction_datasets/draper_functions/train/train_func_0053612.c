add_disk(const gchar *name, gint order, gint device_number, gint unit_number)
	{
	DiskData	*disk;
	GList		*list;
	gint		i;

	disk = g_new0(DiskData, 1);
	disk->name = g_strdup(name);
	disk->order = order;
	disk->subdisk = -1;
	disk->device_number = device_number;
	disk->unit_number = unit_number;
	if (order >= 0)
		{
		for (i = 0, list = disk_list; list; list = list->next, ++i)
			if (disk->order < ((DiskData *) list->data)->order)
				break;
		disk_list = g_list_insert(disk_list, disk, i);
		}
	else
		disk_list = g_list_append(disk_list, disk);
	++n_disks;
	return disk;
	}
