drm_legacy_rmmap_ioctl(struct drm_device *dev, void *data,
			   struct drm_file *file_priv)
{
	struct drm_map *request = data;
	struct drm_local_map *map = NULL;
	struct drm_map_list *r_list;
	int ret;

	mutex_lock(&dev->struct_mutex);
	list_for_each_entry(r_list, &dev->maplist, head) {
		if (r_list->map &&
		    r_list->user_token == (unsigned long)request->handle &&
		    r_list->map->flags & _DRM_REMOVABLE) {
			map = r_list->map;
			break;
		}
	}


	if (list_empty(&dev->maplist) || !map) {
		mutex_unlock(&dev->struct_mutex);
		return -EINVAL;
	}


	if ((map->type == _DRM_REGISTERS) || (map->type == _DRM_FRAME_BUFFER)) {
		mutex_unlock(&dev->struct_mutex);
		return 0;
	}

	ret = drm_legacy_rmmap_locked(dev, map);

	mutex_unlock(&dev->struct_mutex);

	return ret;
}
