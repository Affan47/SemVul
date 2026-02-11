rio_mport_get_physefb(struct rio_mport *port, int local,
		      u16 destid, u8 hopcount)
{
	u32 ext_ftr_ptr;
	u32 ftr_header;

	ext_ftr_ptr = rio_mport_get_efb(port, local, destid, hopcount, 0);

	while (ext_ftr_ptr)  {
		if (local)
			rio_local_read_config_32(port, ext_ftr_ptr,
						 &ftr_header);
		else
			rio_mport_read_config_32(port, destid, hopcount,
						 ext_ftr_ptr, &ftr_header);

		ftr_header = RIO_GET_BLOCK_ID(ftr_header);
		switch (ftr_header) {

		case RIO_EFB_SER_EP_ID_V13P:
		case RIO_EFB_SER_EP_REC_ID_V13P:
		case RIO_EFB_SER_EP_FREE_ID_V13P:
		case RIO_EFB_SER_EP_ID:
		case RIO_EFB_SER_EP_REC_ID:
		case RIO_EFB_SER_EP_FREE_ID:
		case RIO_EFB_SER_EP_FREC_ID:

			return ext_ftr_ptr;

		default:
			break;
		}

		ext_ftr_ptr = rio_mport_get_efb(port, local, destid,
						hopcount, ext_ftr_ptr);
	}

	return ext_ftr_ptr;
}
