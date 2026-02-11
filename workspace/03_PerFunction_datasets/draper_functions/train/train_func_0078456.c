ddf1_cr_off_maxpds_helper(struct ddf1 * ddf1)
{
	struct ddf1_header *h = ddf1->primary;


	return (h->max_primary_elements == 0xFFFF) ?
		h->max_phys_drives : h->max_primary_elements;
}
