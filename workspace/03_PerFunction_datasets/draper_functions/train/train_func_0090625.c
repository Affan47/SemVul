drmModeGetProperty(int fd, uint32_t property_id)
{
	struct drm_mode_get_property prop;
	drmModePropertyPtr r;

	VG_CLEAR(prop);
	prop.prop_id = property_id;
	prop.count_enum_blobs = 0;
	prop.count_values = 0;
	prop.flags = 0;
	prop.enum_blob_ptr = 0;
	prop.values_ptr = 0;

	if (drmIoctl(fd, DRM_IOCTL_MODE_GETPROPERTY, &prop))
		return 0;

	if (prop.count_values)
		prop.values_ptr = VOID2U64(drmMalloc(prop.count_values * sizeof(uint64_t)));

	if (prop.count_enum_blobs && (prop.flags & (DRM_MODE_PROP_ENUM | DRM_MODE_PROP_BITMASK)))
		prop.enum_blob_ptr = VOID2U64(drmMalloc(prop.count_enum_blobs * sizeof(struct drm_mode_property_enum)));

	if (prop.count_enum_blobs && (prop.flags & DRM_MODE_PROP_BLOB)) {
		prop.values_ptr = VOID2U64(drmMalloc(prop.count_enum_blobs * sizeof(uint32_t)));
		prop.enum_blob_ptr = VOID2U64(drmMalloc(prop.count_enum_blobs * sizeof(uint32_t)));
	}

	if (drmIoctl(fd, DRM_IOCTL_MODE_GETPROPERTY, &prop)) {
		r = NULL;
		goto err_allocs;
	}

	if (!(r = drmMalloc(sizeof(*r))))
		return NULL;

	r->prop_id = prop.prop_id;
	r->count_values = prop.count_values;

	r->flags = prop.flags;
	if (prop.count_values)
		r->values = drmAllocCpy(U642VOID(prop.values_ptr), prop.count_values, sizeof(uint64_t));
	if (prop.flags & (DRM_MODE_PROP_ENUM | DRM_MODE_PROP_BITMASK)) {
		r->count_enums = prop.count_enum_blobs;
		r->enums = drmAllocCpy(U642VOID(prop.enum_blob_ptr), prop.count_enum_blobs, sizeof(struct drm_mode_property_enum));
	} else if (prop.flags & DRM_MODE_PROP_BLOB) {
		r->values = drmAllocCpy(U642VOID(prop.values_ptr), prop.count_enum_blobs, sizeof(uint32_t));
		r->blob_ids = drmAllocCpy(U642VOID(prop.enum_blob_ptr), prop.count_enum_blobs, sizeof(uint32_t));
		r->count_blobs = prop.count_enum_blobs;
	}
	strncpy(r->name, prop.name, DRM_PROP_NAME_LEN);
	r->name[DRM_PROP_NAME_LEN-1] = 0;

err_allocs:
	drmFree(U642VOID(prop.values_ptr));
	drmFree(U642VOID(prop.enum_blob_ptr));

	return r;
}
