device_list_free (struct qemu_device_list *l)
{
	if (!l)
		return;

	while (l->head)
		device_free (l->head);
}
