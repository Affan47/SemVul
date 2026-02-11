diskio_init(void)
{
	if (dt->flags & DISKIO_INIT)
		return;

	MEMBER_OFFSET_INIT(class_devices, "class", "class_devices");
	if (INVALID_MEMBER(class_devices))
		MEMBER_OFFSET_INIT(class_devices, "class", "devices");
	MEMBER_OFFSET_INIT(class_p, "class", "p");
	MEMBER_OFFSET_INIT(class_private_devices, "class_private",
		"class_devices");
	MEMBER_OFFSET_INIT(device_knode_class, "device", "knode_class");
	MEMBER_OFFSET_INIT(device_node, "device", "node");
	MEMBER_OFFSET_INIT(device_type, "device", "type");
	MEMBER_OFFSET_INIT(gendisk_dev, "gendisk", "dev");
	if (INVALID_MEMBER(gendisk_dev))
		MEMBER_OFFSET_INIT(gendisk_dev, "gendisk", "__dev");
	MEMBER_OFFSET_INIT(gendisk_kobj, "gendisk", "kobj");
	MEMBER_OFFSET_INIT(gendisk_part0, "gendisk", "part0");
	MEMBER_OFFSET_INIT(gendisk_queue, "gendisk", "queue");
	MEMBER_OFFSET_INIT(hd_struct_dev, "hd_struct", "__dev");
	MEMBER_OFFSET_INIT(klist_k_list, "klist", "k_list");
	MEMBER_OFFSET_INIT(klist_node_n_klist, "klist_node", "n_klist");
	MEMBER_OFFSET_INIT(klist_node_n_node, "klist_node", "n_node");
	MEMBER_OFFSET_INIT(kobject_entry, "kobject", "entry");
	MEMBER_OFFSET_INIT(kset_list, "kset", "list");
	MEMBER_OFFSET_INIT(request_list_count, "request_list", "count");
	MEMBER_OFFSET_INIT(request_queue_in_flight, "request_queue",
		"in_flight");
	if (MEMBER_EXISTS("request_queue", "rq"))
		MEMBER_OFFSET_INIT(request_queue_rq, "request_queue", "rq");
	else
		MEMBER_OFFSET_INIT(request_queue_rq, "request_queue", "root_rl");
	MEMBER_OFFSET_INIT(subsys_private_klist_devices, "subsys_private",
		"klist_devices");
	MEMBER_OFFSET_INIT(subsystem_kset, "subsystem", "kset");
	STRUCT_SIZE_INIT(subsystem, "subsystem");
	STRUCT_SIZE_INIT(class_private, "class_private");
	MEMBER_SIZE_INIT(rq_in_flight, "request_queue", "in_flight");
	MEMBER_SIZE_INIT(class_private_devices, "class_private",
		"class_devices");

	dt->flags |= DISKIO_INIT;
}
