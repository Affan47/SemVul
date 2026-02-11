cm_tdbush_object_type_map_get_n(unsigned int i)
{
	if (i < (sizeof(cm_tdbush_object_type_map) /
		 sizeof(cm_tdbush_object_type_map[0]))) {
		return cm_tdbush_object_type_map + i;
	} else {
		return NULL;
	}
}
