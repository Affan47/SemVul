s2io_vpd_read(struct s2io_nic *nic)
{
	u8 *vpd_data;
	u8 data;
	int i = 0, cnt, len, fail = 0;
	int vpd_addr = 0x80;
	struct swStat *swstats = &nic->mac_control.stats_info->sw_stat;

	if (nic->device_type == XFRAME_II_DEVICE) {
		strcpy(nic->product_name, "Xframe II 10GbE network adapter");
		vpd_addr = 0x80;
	} else {
		strcpy(nic->product_name, "Xframe I 10GbE network adapter");
		vpd_addr = 0x50;
	}
	strcpy(nic->serial_num, "NOT AVAILABLE");

	vpd_data = kmalloc(256, GFP_KERNEL);
	if (!vpd_data) {
		swstats->mem_alloc_fail_cnt++;
		return;
	}
	swstats->mem_allocated += 256;

	for (i = 0; i < 256; i += 4) {
		pci_write_config_byte(nic->pdev, (vpd_addr + 2), i);
		pci_read_config_byte(nic->pdev,  (vpd_addr + 2), &data);
		pci_write_config_byte(nic->pdev, (vpd_addr + 3), 0);
		for (cnt = 0; cnt < 5; cnt++) {
			msleep(2);
			pci_read_config_byte(nic->pdev, (vpd_addr + 3), &data);
			if (data == 0x80)
				break;
		}
		if (cnt >= 5) {
			DBG_PRINT(ERR_DBG, "Read of VPD data failed\n");
			fail = 1;
			break;
		}
		pci_read_config_dword(nic->pdev,  (vpd_addr + 4),
				      (u32 *)&vpd_data[i]);
	}

	if (!fail) {

		for (cnt = 0; cnt < 252; cnt++) {
			if ((vpd_data[cnt] == 'S') &&
			    (vpd_data[cnt+1] == 'N')) {
				len = vpd_data[cnt+2];
				if (len < min(VPD_STRING_LEN, 256-cnt-2)) {
					memcpy(nic->serial_num,
					       &vpd_data[cnt + 3],
					       len);
					memset(nic->serial_num+len,
					       0,
					       VPD_STRING_LEN-len);
					break;
				}
			}
		}
	}

	if ((!fail) && (vpd_data[1] < VPD_STRING_LEN)) {
		len = vpd_data[1];
		memcpy(nic->product_name, &vpd_data[3], len);
		nic->product_name[len] = 0;
	}
	kfree(vpd_data);
	swstats->mem_freed += 256;
}
