scc_lu_init(struct scsi_lu *lu)
{
	if (spc_lu_init(lu))
		return TGTADM_NOMEM;

	strncpy(lu->attrs.product_id, "Controller",
		sizeof(lu->attrs.product_id));
	lu->attrs.version_desc[0] = 0x04C0;
	lu->attrs.version_desc[1] = 0x0960;
	lu->attrs.version_desc[2] = 0x01fb;

	lu->dev_type_template.lu_online(lu);

	return 0;
}
