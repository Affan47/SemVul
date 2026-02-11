mmc_lu_init(struct scsi_lu *lu)
{
	struct backingstore_template *bst;
	struct mmc_info *mmc;

	mmc = zalloc(sizeof(struct mmc_info));
	if (!mmc)
		return -ENOMEM;

	lu->xxc_p = mmc;

	if (spc_lu_init(lu))
		return TGTADM_NOMEM;


	bst = get_backingstore_template("rdwr");
	if (!bst) {
		eprintf("failed to find bstype, rdwr\n");
		return TGTADM_INVALID_REQUEST;
	}
	lu->bst = bst;

	strncpy(lu->attrs.product_id, "VIRTUAL-CDROM",
		sizeof(lu->attrs.product_id));
	lu->attrs.sense_format = 0;
	lu->attrs.version_desc[0] = 0x02A0;
	lu->attrs.version_desc[1] = 0x0960;
	lu->attrs.version_desc[2] = 0x0300;

	lu->attrs.removable = 1;


	add_mode_page(lu, "0:0:0");

	add_mode_page(lu, "1:0:10:0:8:0:0:0:0:8:0:0:0");

	add_mode_page(lu, "3:0:6:0:0:0:0:0:0");


	add_mode_page(lu, "8:0:10:0:0:0:0:0:0:0:0:0:0");

	add_mode_page(lu, "10:0:10:2:0:0:0:0:0:0:0:2:0");

	add_mode_page(lu, "0x1a:0:10:8:0:0:0:0:0:0:0:0:0");

	add_mode_page(lu, "0x1c:0:10:8:0:0:0:0:0:0:0:0:0");

	add_mode_page(lu, "0x1d:0:10:0:0:7:0:0:2:0:2:0:20");

	add_mode_page(lu, "0x2a:0x00:0x3e:0x3f:0x37:0xf3:0xf3:0x29:"
			  "0x23:0x10:0x8a:0x01:0x00:0x08:0x00:0x10:"
			  "0x8a:0x00:0x00:0x10:0x8a:0x10:0x8a:0x00:"
			  "0x01:0x00:0x00:0x00:0x00:0x10:0x8a:0x00:"
			  "0x05:0x00:0x00:0x10:0x8a:0x00:0x00:0x0b:"
			  "0x06:0x00:0x00:0x08:0x45:0x00:0x00:0x05:"
			  "0x83:0x00:0x00:0x02:0xc2:0x00:0x00:0x00:"
			  "0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00:"
			  "0x00");

	add_mode_page(lu, "0x05:0:0x32:0x62:5:8:0x10:0:0:0:0:0:0:0:"
			  "0x10:0:0x96:0:0:0:0:0:0:0:0:0:0:0:0:0:0:"
			  "0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:"
			  "0:0");
	return 0;
}
