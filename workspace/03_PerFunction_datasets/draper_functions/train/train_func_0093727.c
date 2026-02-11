__uvc_find_control(struct uvc_entity *entity, __u32 v4l2_id,
	struct uvc_control_mapping **mapping, struct uvc_control **control,
	int next)
{
	struct uvc_control *ctrl;
	struct uvc_control_mapping *map;
	unsigned int i;

	if (entity == NULL)
		return;

	for (i = 0; i < entity->ncontrols; ++i) {
		ctrl = &entity->controls[i];
		if (!ctrl->initialized)
			continue;

		list_for_each_entry(map, &ctrl->info.mappings, list) {
			if ((map->id == v4l2_id) && !next) {
				*control = ctrl;
				*mapping = map;
				return;
			}

			if ((*mapping == NULL || (*mapping)->id > map->id) &&
			    (map->id > v4l2_id) && next) {
				*control = ctrl;
				*mapping = map;
			}
		}
	}
}
