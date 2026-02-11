ata_scsiop_inq_b0(struct ata_scsi_args *args, u8 *rbuf)
{
	u16 min_io_sectors;

	rbuf[1] = 0xb0;
	rbuf[3] = 0x3c;


	min_io_sectors = 1 << ata_id_log2_per_physical_sector(args->id);
	put_unaligned_be16(min_io_sectors, &rbuf[6]);


	if (ata_id_has_trim(args->id)) {
		put_unaligned_be64(65535 * 512 / 8, &rbuf[36]);
		put_unaligned_be32(1, &rbuf[28]);
	}

	return 0;
}
