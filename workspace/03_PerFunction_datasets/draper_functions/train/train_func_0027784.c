usb_amd_hang_symptom_quirk(void)
{
	u8 rev;

	usb_amd_find_chipset_info();
	rev = amd_chipset.sb_type.rev;

	return amd_chipset.sb_type.gen == AMD_CHIPSET_SB600 ||
			(amd_chipset.sb_type.gen == AMD_CHIPSET_SB700 &&
			 rev >= 0x3a && rev <= 0x3b);
}
