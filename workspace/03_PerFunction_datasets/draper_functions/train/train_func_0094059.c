gkrellm_disk_assign_data_nth(gint n, guint64 rb, guint64 wb, gboolean virtual)
	{
	DiskMon	*disk;
	gchar	name[32], label[32];

	assign_method = DISK_ASSIGN_NTH;
	if (n < n_disks)
		disk = (DiskMon *) g_list_nth_data(disk_mon_list, n + 1);
	else
		{
		snprintf(name, sizeof(name), "%s%c", "Disk", 'A' + n);
		snprintf(label, sizeof(label), "%s%c", _("Disk"), 'A' + n);
		disk = add_disk(name, label, 0, 0, n);
		}
	disk_assign_data(disk, rb, wb, virtual);
	}
