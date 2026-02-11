brasero_medium_get_css_feature (BraseroMedium *self,
				BraseroDeviceHandle *handle,
				BraseroScsiErrCode *code)
{
	BraseroScsiGetConfigHdr *hdr = NULL;
	BraseroMediumPrivate *priv;
	BraseroScsiResult result;
	int size;

	priv = BRASERO_MEDIUM_PRIVATE (self);

	BRASERO_MEDIA_LOG ("Testing for Css encrypted media");
	result = brasero_mmc2_get_configuration_feature (handle,
							 BRASERO_SCSI_FEAT_DVD_CSS,
							 &hdr,
							 &size,
							 code);
	if (result != BRASERO_SCSI_OK) {
		BRASERO_MEDIA_LOG ("GET CONFIGURATION failed");
		return FALSE;
	}

	if (hdr->desc->add_len < sizeof (BraseroScsiDVDCssDesc)) {
		g_free (hdr);
		return TRUE;
	}


	if (hdr->desc->current) {
		priv->info |= BRASERO_MEDIUM_PROTECTED;
		BRASERO_MEDIA_LOG ("media is Css protected");
	}

	g_free (hdr);
	return TRUE;
}
