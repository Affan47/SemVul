updateMaps(int32_t vol)
{
	int rc;
	struct dinode *dip;
	pxd_t pxd1;


	PXDaddress(&pxd1, (AITBL_OFF + (SIZE_OF_MAP_PAGE << 1)) >> vopen[vol].l2bsize);
	PXDlength(&pxd1, vopen[vol].lbperpage);
	if ((rc = bread(vol, pxd1, (void **) &dip, PB_READ)) != 0) {
		fsck_send_msg(lrdo_UMPREADIMAPINOFAIL);
		return (IMAP_READERROR5);
	}


	dip += FILESYSTEM_I & 0x07;


	if ((rc = writeImap(vol, vopen[vol].fsimap_lst, dip)) != 0) {
		fsck_send_msg(lrdo_UMPWRITEIMAPCTLFAIL);
		return (rc);
	}


	if (!Insuff_memory_for_maps) {

		PXDaddress(&pxd1, AITBL_OFF >> vopen[vol].l2bsize);
		if ((rc = bread(vol, pxd1, (void **) &dip, PB_READ)) != 0) {
			fsck_send_msg(lrdo_UMPREADBMAPINOFAIL);
			return (BMAP_READERROR4);
		}


		dip += BMAP_I;


		if ((rc = writeBmap(vol, vopen[vol].bmap_ctl, dip)) != 0) {
			fsck_send_msg(lrdo_UMPWRITEBMAPCTLFAIL);
		}
	}

	return (rc);
}
