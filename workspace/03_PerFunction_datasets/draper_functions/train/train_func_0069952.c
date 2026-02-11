osd_sec_init_nosec_doall_caps(void *caps,
	const struct osd_obj_id *obj, bool is_collection, const bool is_v1)
{
	struct osd_capability *cap = caps;
	u8 type;
	u8 descriptor_type;

	if (likely(obj->id)) {
		if (unlikely(is_collection)) {
			type = OSD_SEC_OBJ_COLLECTION;
			descriptor_type = is_v1 ? OSD_SEC_OBJ_DESC_OBJ :
						  OSD_SEC_OBJ_DESC_COL;
		} else {
			type = OSD_SEC_OBJ_USER;
			descriptor_type = OSD_SEC_OBJ_DESC_OBJ;
		}
		WARN_ON(!obj->partition);
	} else {
		type = obj->partition ? OSD_SEC_OBJ_PARTITION :
					OSD_SEC_OBJ_ROOT;
		descriptor_type = OSD_SEC_OBJ_DESC_PAR;
	}

	memset(cap, 0, sizeof(*cap));

	cap->h.format = OSD_SEC_CAP_FORMAT_VER1;
	cap->h.integrity_algorithm__key_version = 0;
	cap->h.security_method = OSD_SEC_NOSEC;


	cap->h.object_type = type;
	osd_sec_set_caps(&cap->h, OSD_SEC_CAP_V1_ALL_CAPS);
	cap->h.object_descriptor_type = descriptor_type;
	cap->od.obj_desc.policy_access_tag = 0;
	cap->od.obj_desc.allowed_partition_id = cpu_to_be64(obj->partition);
	cap->od.obj_desc.allowed_object_id = cpu_to_be64(obj->id);
}
