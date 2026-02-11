mc_mac_equal (const mac_t *mac1, const mac_t *mac2)
{
	int i;
	for (i=0; i<6; i++) {
		if (mac1->byte[i] != mac2->byte[i]) {
			return 0;
		}
	}
	return 1;
}
