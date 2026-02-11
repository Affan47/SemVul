istgt_lu_tape_scsi_mode_sense6(ISTGT_LU_TAPE *spec, CONN_Ptr conn, uint8_t *cdb, int dbd, int pc, int page, int subpage, uint8_t *data, int alloc_len)
{
	uint8_t *cp;
	int hlen = 0, len = 0, plen;
	int total;
	int llbaa = 0;

	data[0] = 0;
	if (spec->mload) {


		data[1] = MEDIATYPE_DFLT;
		data[2] = 0;
		if (spec->lu->readonly
			|| (spec->mflags & ISTGT_LU_FLAG_MEDIA_READONLY)) {
			BDADD8(&data[2], 1, 7);
		}
	} else {
		data[1] = 0;
		data[2] = 0;
	}
	BDADD8W(&data[2], 1, 6, 3);
	data[3] = 0;
	hlen = 4;

	cp = &data[4];
	if (dbd) {
		len = 0;
	} else {
		if (llbaa) {
			if (spec->mload) {

				DSET64(&cp[0], 0ULL);

				DSET32(&cp[8], 0);

				DSET32(&cp[12], (uint32_t) spec->lblen);
			} else {

				DSET64(&cp[0], 0ULL);

				DSET32(&cp[8], 0);

				DSET32(&cp[12], 0);
			}
			len = 16;
		} else {
			if (spec->mload) {

				DSET32(&cp[0], 0);

				DSET32(&cp[4], (uint32_t) spec->lblen);
				cp[0] = DENSITY_DFLT;
				cp[4] = 0;
			} else {

				DSET32(&cp[0], 0);

				DSET32(&cp[4], 0);
				cp[0] = 0;
				cp[4] = 0;
			}
			len = 8;
		}
		cp += len;
	}
	data[3] = len;

	plen = istgt_lu_tape_scsi_mode_sense_page(spec, conn, cdb, pc, page, subpage, &cp[0], alloc_len);
	cp += plen;

	total = hlen + len + plen;
	data[0] = total - 1;

	return total;
}
