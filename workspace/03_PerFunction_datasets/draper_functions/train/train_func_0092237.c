pm8001_alloc_dev(struct pm8001_hba_info *pm8001_ha)
{
	u32 dev;
	for (dev = 0; dev < PM8001_MAX_DEVICES; dev++) {
		if (pm8001_ha->devices[dev].dev_type == SAS_PHY_UNUSED) {
			pm8001_ha->devices[dev].id = dev;
			return &pm8001_ha->devices[dev];
		}
	}
	if (dev == PM8001_MAX_DEVICES) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("max support %d devices, ignore ..\n",
			PM8001_MAX_DEVICES));
	}
	return NULL;
}
