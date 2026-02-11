it821x_read_id(struct ata_device *adev,
					struct ata_taskfile *tf, u16 *id)
{
	unsigned int err_mask;
	unsigned char model_num[ATA_ID_PROD_LEN + 1];

	err_mask = ata_do_dev_read_id(adev, tf, id);
	if (err_mask)
		return err_mask;
	ata_id_c_string(id, model_num, ATA_ID_PROD, sizeof(model_num));

	id[83] &= ~(1 << 12);
	id[83] &= ~(1 << 13);
	id[84] &= ~(1 << 6);
	id[85] &= ~(1 << 10);
	id[76] = 0;

	if (strstr(model_num, "Integrated Technology Express")) {

		id[49] |= 0x0300;
		id[83] &= 0x7FFF;
		id[83] |= 0x4400;
		id[86] |= 0x0400;
		id[ATA_ID_MAJOR_VER] |= 0x1F;


		memset(&id[ATA_ID_SERNO], 0x20, ATA_ID_SERNO_LEN);
	}
	return err_mask;
}
