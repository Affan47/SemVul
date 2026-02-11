remove_mount(mount_list_t * current_mount)
{
	if (current_mount->auto_unmount_time != INT64_MAX)
		auto_unmount_ph_remove(&auto_unmount_ph, current_mount);

	free(current_mount->root_name);
	free(current_mount->mount_point);
	if (current_mount->prev)
		current_mount->prev->next = current_mount->next;
	else
		mount_list = current_mount->next;
	if (current_mount->next)
		current_mount->next->prev = current_mount->prev;
	free(current_mount);
	update_auto_unmount(NULL);
}
