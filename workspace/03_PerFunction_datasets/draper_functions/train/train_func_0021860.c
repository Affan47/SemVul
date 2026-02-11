smb2_calc_size(void *buf)
{
	struct smb2_pdu *pdu = (struct smb2_pdu *)buf;
	struct smb2_hdr *hdr = &pdu->hdr;
	struct smb2_sync_hdr *shdr = get_sync_hdr(hdr);
	int offset;
	int data_length;

	int len = 4 + le16_to_cpu(shdr->StructureSize);


	len += le16_to_cpu(pdu->StructureSize2);

	if (has_smb2_data_area[le16_to_cpu(shdr->Command)] == false)
		goto calc_size_exit;

	smb2_get_data_area_len(&offset, &data_length, hdr);
	cifs_dbg(FYI, "SMB2 data length %d offset %d\n", data_length, offset);

	if (data_length > 0) {


		if (offset + 4 + 1 < len) {
			cifs_dbg(VFS, "data area offset %d overlaps SMB2 header %d\n",
				 offset + 4 + 1, len);
			data_length = 0;
		} else {
			len = 4 + offset + data_length;
		}
	}
calc_size_exit:
	cifs_dbg(FYI, "SMB2 len %d\n", len);
	return len;
}
