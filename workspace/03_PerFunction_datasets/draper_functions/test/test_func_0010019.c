cciss_alloc_drive_info(ctlr_info_t *h, int controller_node)
{
	int i;
	drive_info_struct *drv;


	for (i = 0; i < CISS_MAX_LUN; i++) {


		if (h->drv[i] && i != 0)
			continue;


		if (i == 0 && h->drv[i] && h->drv[i]->raid_level != -1)
			continue;


		if (i > h->highest_lun && !controller_node)
			h->highest_lun = i;


		if (i == 0 && h->drv[i] != NULL)
			return i;


		drv = kzalloc(sizeof(*drv), GFP_KERNEL);
		if (!drv)
			return -1;
		drv->raid_level = -1;
		h->drv[i] = drv;
		return i;
	}
	return -1;
}
