adf_devmgr_add_dev(struct adf_accel_dev *accel_dev,
		       struct adf_accel_dev *pf)
{
	struct list_head *itr;
	int ret = 0;

	if (num_devices == ADF_MAX_DEVICES) {
		dev_err(&GET_DEV(accel_dev), "Only support up to %d devices\n",
			ADF_MAX_DEVICES);
		return -EFAULT;
	}

	mutex_lock(&table_lock);
	atomic_set(&accel_dev->ref_count, 0);


	if (!accel_dev->is_vf || (accel_dev->is_vf && !pf)) {
		struct vf_id_map *map;

		list_for_each(itr, &accel_table) {
			struct adf_accel_dev *ptr =
				list_entry(itr, struct adf_accel_dev, list);

			if (ptr == accel_dev) {
				ret = -EEXIST;
				goto unlock;
			}
		}

		list_add_tail(&accel_dev->list, &accel_table);
		accel_dev->accel_id = num_devices++;

		map = kzalloc(sizeof(*map), GFP_KERNEL);
		if (!map) {
			ret = -ENOMEM;
			goto unlock;
		}
		map->bdf = ~0;
		map->id = accel_dev->accel_id;
		map->fake_id = map->id;
		map->attached = true;
		list_add_tail(&map->list, &vfs_table);
	} else if (accel_dev->is_vf && pf) {

		struct adf_accel_vf_info *vf_info;
		struct vf_id_map *map;

		vf_info = pf->pf.vf_info + adf_get_vf_id(accel_dev);

		map = adf_find_vf(adf_get_vf_num(accel_dev));
		if (map) {
			struct vf_id_map *next;

			accel_dev->accel_id = map->id;
			list_add_tail(&accel_dev->list, &accel_table);
			map->fake_id++;
			map->attached = true;
			next = list_next_entry(map, list);
			while (next && &next->list != &vfs_table) {
				next->fake_id++;
				next = list_next_entry(next, list);
			}

			ret = 0;
			goto unlock;
		}

		map = kzalloc(sizeof(*map), GFP_KERNEL);
		if (!map) {
			ret = -ENOMEM;
			goto unlock;
		}

		accel_dev->accel_id = num_devices++;
		list_add_tail(&accel_dev->list, &accel_table);
		map->bdf = adf_get_vf_num(accel_dev);
		map->id = accel_dev->accel_id;
		map->fake_id = map->id;
		map->attached = true;
		list_add_tail(&map->list, &vfs_table);
	}
unlock:
	mutex_unlock(&table_lock);
	return ret;
}
