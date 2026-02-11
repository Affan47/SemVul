get_phys_drive(struct ddf1 *ddf1)
{
	unsigned int i = ddf1->pd_header->max_drives;

	while (i--) {
		if (ddf1->pds[i].reference == ddf1->disk_data->reference)
			return ddf1->pds + i;
	}

	return NULL;
}
