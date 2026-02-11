ipack_parse_id2(struct ipack_device *dev)
{
	__be16 *id = (__be16 *) dev->id;
	u16 flags, crc;

	dev->id_vendor = ((be16_to_cpu(id[3]) & 0xff) << 16)
			 + be16_to_cpu(id[4]);
	dev->id_device = be16_to_cpu(id[5]);
	flags = be16_to_cpu(id[10]);
	dev->speed_8mhz = !!(flags & 2);
	dev->speed_32mhz = !!(flags & 4);
	crc = ipack_calc_crc2(dev);
	dev->id_crc_correct = (crc == be16_to_cpu(id[12]));
	if (!dev->id_crc_correct) {
		dev_warn(&dev->dev, "ID CRC invalid found 0x%x, expected 0x%x.\n",
				id[11], crc);
	}
}
