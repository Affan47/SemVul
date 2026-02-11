acpi_video_register(void)
{
	int ret = 0;

	mutex_lock(&register_count_mutex);
	if (register_count) {


		goto leave;
	}

	mutex_init(&video_list_lock);
	INIT_LIST_HEAD(&video_bus_head);

	dmi_check_system(video_dmi_table);

	ret = acpi_bus_register_driver(&acpi_video_bus);
	if (ret)
		goto leave;


	register_count = 1;

leave:
	mutex_unlock(&register_count_mutex);
	return ret;
}
