rt2500pci_set_vgc(struct rt2x00_dev *rt2x00dev,
				     struct link_qual *qual, u8 vgc_level)
{
	if (qual->vgc_level_reg != vgc_level) {
		rt2500pci_bbp_write(rt2x00dev, 17, vgc_level);
		qual->vgc_level = vgc_level;
		qual->vgc_level_reg = vgc_level;
	}
}
