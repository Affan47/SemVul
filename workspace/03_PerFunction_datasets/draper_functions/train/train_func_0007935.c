asd_read_ocm_dir(struct asd_ha_struct *asd_ha,
			    struct asd_ocm_dir *dir, u32 offs)
{
	int err = asd_read_ocm_seg(asd_ha, dir, offs, sizeof(*dir));
	if (err) {
		ASD_DPRINTK("couldn't read ocm segment\n");
		return err;
	}

	if (dir->sig[0] != 'M' || dir->sig[1] != 'O') {
		ASD_DPRINTK("no valid dir signature(%c%c) at start of OCM\n",
			    dir->sig[0], dir->sig[1]);
		return -ENOENT;
	}
	if (dir->major != 0) {
		asd_printk("unsupported major version of ocm dir:0x%x\n",
			   dir->major);
		return -ENOENT;
	}
	dir->num_de &= 0xf;
	return 0;
}
