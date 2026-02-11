bnxt_flash_microcode(struct net_device *dev,
				u16 dir_type,
				const u8 *fw_data,
				size_t fw_size)
{
	struct bnxt_ucode_trailer *trailer;
	u32 calculated_crc;
	u32 stored_crc;
	int rc = 0;

	if (fw_size < sizeof(struct bnxt_ucode_trailer)) {
		netdev_err(dev, "Invalid microcode file size: %u\n",
			   (unsigned int)fw_size);
		return -EINVAL;
	}
	trailer = (struct bnxt_ucode_trailer *)(fw_data + (fw_size -
						sizeof(*trailer)));
	if (trailer->sig != cpu_to_le32(BNXT_UCODE_TRAILER_SIGNATURE)) {
		netdev_err(dev, "Invalid microcode trailer signature: %08X\n",
			   le32_to_cpu(trailer->sig));
		return -EINVAL;
	}
	if (le16_to_cpu(trailer->dir_type) != dir_type) {
		netdev_err(dev, "Expected microcode type: %d, read: %d\n",
			   dir_type, le16_to_cpu(trailer->dir_type));
		return -EINVAL;
	}
	if (le16_to_cpu(trailer->trailer_length) <
		sizeof(struct bnxt_ucode_trailer)) {
		netdev_err(dev, "Invalid microcode trailer length: %d\n",
			   le16_to_cpu(trailer->trailer_length));
		return -EINVAL;
	}


	stored_crc = le32_to_cpu(*(__le32 *)(fw_data + fw_size -
					     sizeof(stored_crc)));
	calculated_crc = ~crc32(~0, fw_data, fw_size - sizeof(stored_crc));
	if (calculated_crc != stored_crc) {
		netdev_err(dev,
			   "CRC32 (%08lX) does not match calculated: %08lX\n",
			   (unsigned long)stored_crc,
			   (unsigned long)calculated_crc);
		return -EINVAL;
	}
	rc = bnxt_flash_nvram(dev, dir_type, BNX_DIR_ORDINAL_FIRST,
			      0, 0, fw_data, fw_size);

	return rc;
}
