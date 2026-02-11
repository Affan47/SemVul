nvme_trans_fill_control_page(struct nvme_ns *ns,
					struct sg_io_hdr *hdr, u8 *resp,
					int len)
{
	if (len < MODE_PAGE_CONTROL_LEN)
		return -EINVAL;

	resp[0] = MODE_PAGE_CONTROL;
	resp[1] = MODE_PAGE_CONTROL_LEN_FIELD;
	resp[2] = 0x0E;

	resp[3] = 0x12;

	resp[5] = 0x40;

	resp[8] = 0xFF;
	resp[9] = 0xFF;


	return 0;
}
