iMapWrite(int vol,
	      int32_t page_number,
	      void *page_buffer)
{
	int imw_rc = 0;


	imw_rc = ujfs_rw_diskblocks(vopen[vol].fp,
				    vopen[vol].fsimap_lst.imap_wsp[page_number].page_offset,
				    PSIZE, page_buffer, PUT);
	if (imw_rc != 0) {
		fsck_send_msg(lrdo_WRIMPBLKWRITEFAIL,
			      (long long)vopen[vol].bmap_wsp[page_number].page_offset);
		return (IMAP_WRITEERROR2);
	}

	return (imw_rc);
}
