add_subdisk(const gchar *subdisk_name, const gchar *disk_name, gint subdisk)
	{
	DiskMon	*disk, *sdisk;
	GList	*list = NULL;

	for (list = disk_mon_list->next; list; list = list->next)
		{
		disk = (DiskMon * ) list->data;
		if (!strcmp(disk_name, disk->name))
			break;
		}
	if (!list)
		return NULL;
	sdisk = disk_new(subdisk_name, subdisk_name);
	sdisk->order = disk->order;
	sdisk->subdisk = subdisk;
	for (list = list->next; list; list = list->next)
		{
		disk = (DiskMon * ) list->data;
		if (disk->subdisk == -1 || disk->subdisk > subdisk)
			break;
		}
	disk_mon_list = g_list_insert_before(disk_mon_list, list, sdisk);
	++n_disks;
	return sdisk;
	}
