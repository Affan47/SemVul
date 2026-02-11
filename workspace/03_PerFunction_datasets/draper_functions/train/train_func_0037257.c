TTD_GetCapabilities(GF_BaseDecoder *plug, GF_CodecCapability *capability)
{
	TTDPriv *priv = (TTDPriv *)plug->privateStack;
	switch (capability->CapCode) {
	case GF_CODEC_WIDTH:
		capability->cap.valueInt = priv->cfg->text_width;
		return GF_OK;
	case GF_CODEC_HEIGHT:
		capability->cap.valueInt = priv->cfg->text_height;
		return GF_OK;
	case GF_CODEC_MEDIA_NOT_OVER:
		capability->cap.valueInt = priv->is_active;
		return GF_OK;
	default:
		capability->cap.valueInt = 0;
		return GF_OK;
	}
}
