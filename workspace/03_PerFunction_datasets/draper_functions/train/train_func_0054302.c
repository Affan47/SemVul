bnxt_flash_firmware(struct net_device *dev,
			       u16 dir_type,
			       const u8 *fw_data,
			       size_t fw_size)
{
	int	rc = 0;
	u16	code_type;
	u32	stored_crc;
	u32	calculated_crc;
	struct bnxt_fw_header *header = (struct bnxt_fw_header *)fw_data;

	switch (dir_type) {
	case BNX_DIR_TYPE_BOOTCODE:
	case BNX_DIR_TYPE_BOOTCODE_2:
		code_type = CODE_BOOT;
		break;
	default:
		netdev_err(dev, "Unsupported directory entry type: %u\n",
			   dir_type);
		return -EINVAL;
	}
	if (fw_size < sizeof(struct bnxt_fw_header)) {
		netdev_err(dev, "Invalid firmware file size: %u\n",
			   (unsigned int)fw_size);
		return -EINVAL;
	}
	if (header->signature != cpu_to_le32(BNXT_FIRMWARE_BIN_SIGNATURE)) {
		netdev_err(dev, "Invalid firmware signature: %08X\n",
			   le32_to_cpu(header->signature));
		return -EINVAL;
	}
	if (header->code_type != code_type) {
		netdev_err(dev, "Expected firmware type: %d, read: %d\n",
			   code_type, header->code_type);
		return -EINVAL;
	}
	if (header->device != DEVICE_CUMULUS_FAMILY) {
		netdev_err(dev, "Expected firmware device family %d, read: %d\n",
			   DEVICE_CUMULUS_FAMILY, header->device);
		return -EINVAL;
	}

	stored_crc = le32_to_cpu(*(__le32 *)(fw_data + fw_size -
					     sizeof(stored_crc)));
	calculated_crc = ~crc32(~0, fw_data, fw_size - sizeof(stored_crc));
	if (calculated_crc != stored_crc) {
		netdev_err(dev, "Firmware file CRC32 checksum (%08lX) does not match calculated checksum (%08lX)\n",
			   (unsigned long)stored_crc,
			   (unsigned long)calculated_crc);
		return -EINVAL;
	}

	rc = bnxt_flash_nvram(dev, dir_type, BNX_DIR_ORDINAL_FIRST,
			      0, 0, fw_data, fw_size);
	if (rc == 0) {


	}
	return rc;
}
