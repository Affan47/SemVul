intel_815_configure(void)
{
	u32 addr;
	u8 temp2;
	struct aper_size_info_8 *current_size;


	if (agp_bridge->gatt_bus_addr & INTEL_815_ATTBASE_MASK) {
		dev_emerg(&agp_bridge->dev->dev, "gatt bus addr too high");
		return -EINVAL;
	}

	current_size = A_SIZE_8(agp_bridge->current_size);


	pci_write_config_byte(agp_bridge->dev, INTEL_APSIZE,
			current_size->size_value);


	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	pci_read_config_dword(agp_bridge->dev, INTEL_ATTBASE, &addr);
	addr &= INTEL_815_ATTBASE_MASK;
	addr |= agp_bridge->gatt_bus_addr;
	pci_write_config_dword(agp_bridge->dev, INTEL_ATTBASE, addr);


	pci_write_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);


	pci_read_config_byte(agp_bridge->dev, INTEL_815_APCONT, &temp2);
	pci_write_config_byte(agp_bridge->dev, INTEL_815_APCONT, temp2 | (1 << 1));


	return 0;
}
