disk_assign_data(DiskData *disk, guint64 rb, guint64 wb, gboolean virtual)
	{
	if (disk)
		{
		if (disk->rb != rb || disk->wb != wb)
			disk->changed = TRUE;
		else
			disk->changed = FALSE;
		disk->rb = rb;
		disk->wb = wb;
		disk->virtual = virtual;
		}
	}
