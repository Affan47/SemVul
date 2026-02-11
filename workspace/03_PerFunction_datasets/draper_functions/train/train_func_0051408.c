find_cable_id_by_name(struct extcon_dev *edev, const char *name)
{
	int id = -EINVAL;
	int i = 0;


	while (extcon_name[i]) {
		if (!strncmp(extcon_name[i], name, CABLE_NAME_MAX)) {
			id = i;
			break;
		}
		i++;
	}

	return id;
}
