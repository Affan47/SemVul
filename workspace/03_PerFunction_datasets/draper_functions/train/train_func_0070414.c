image_append(struct image * image, const char * type, const char * device, const char * hwrevs, const char * version, const char * layout) {

	enum image_type detected_type;

	image->hash = image_hash_from_data(image);

	image->devices = calloc(1, sizeof(struct device_list));
	if ( ! image->devices )
		return -1;

	image->devices->device = DEVICE_ANY;

	if ( device && device[0] ) {
		image->devices->device = device_from_string(device);
		if ( ! noverify && image->devices->device == DEVICE_UNKNOWN ) {
			ERROR("Specified Device %s is unknown", device);
			image_free(image);
			return -1;
		}
	}

	detected_type = image_type_from_data(image);
	image->type = detected_type;

	if ( type && type[0] ) {
		image->type = image_type_from_string(type);
		if ( ! noverify && image->type == IMAGE_UNKNOWN ) {
			ERROR("Specified Image type %s is unknown", type);
			image_free(image);
			return -1;
		}
		if ( ! noverify && detected_type != image->type && detected_type != IMAGE_UNKNOWN ) {
			ERROR("Image type mishmash (detected %s, got %s)", image_type_to_string(detected_type), type);
			image_free(image);
			return -1;
		}
	}

	if ( hwrevs && hwrevs[0] )
		image->devices->hwrevs = hwrevs_alloc_from_string(hwrevs);
	else
		image->devices->hwrevs = NULL;

	if ( version && version[0] )
		image->version = strdup(version);
	else
		image->version = NULL;

	if ( layout && layout[0] )
		image->layout = strdup(layout);
	else
		image->layout = NULL;

	return 0;

}
