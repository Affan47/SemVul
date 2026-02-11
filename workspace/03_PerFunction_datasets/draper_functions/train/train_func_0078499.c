IMG_GetESD(IMGLoader *read)
{
	GF_ESD *esd = gf_odf_desc_esd_new(0);
	esd->slConfig->timestampResolution = 1000;
	esd->decoderConfig->streamType = GF_STREAM_VISUAL;
	esd->ESID = 1;

	if (read->img_type == IMG_BMP)
		esd->decoderConfig->objectTypeIndication = GPAC_BMP_OTI;
	else {
		u8 OTI=0;
		u32 mtype, w, h;
		GF_BitStream *bs = gf_bs_from_file(read->stream, GF_BITSTREAM_READ);
#ifndef GPAC_DISABLE_AV_PARSERS
		gf_img_parse(bs, &OTI, &mtype, &w, &h, &esd->decoderConfig->decoderSpecificInfo->data, &esd->decoderConfig->decoderSpecificInfo->dataLength);
#endif
		gf_bs_del(bs);

		if (!OTI) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_CODEC, ("[IMG_IN] Unable to guess format image - assigning from extension\n"));
			if (read->img_type==IMG_JPEG) OTI = GPAC_OTI_IMAGE_JPEG;
			else if (read->img_type==IMG_PNG) OTI = GPAC_OTI_IMAGE_PNG;
		}
		esd->decoderConfig->objectTypeIndication = OTI;

		if (read->img_type == IMG_PNGD) {
			GF_Descriptor *d = gf_odf_desc_new(GF_ODF_AUX_VIDEO_DATA);
			((GF_AuxVideoDescriptor*)d)->aux_video_type = 1;
			gf_list_add(esd->extensionDescriptors, d);
		}
		else if (read->img_type == IMG_PNGDS) {
			GF_Descriptor *d = gf_odf_desc_new(GF_ODF_AUX_VIDEO_DATA);
			((GF_AuxVideoDescriptor*)d)->aux_video_type = 2;
			gf_list_add(esd->extensionDescriptors, d);
		}
		else if (read->img_type == IMG_PNGS) {
			GF_Descriptor *d = gf_odf_desc_new(GF_ODF_AUX_VIDEO_DATA);
			((GF_AuxVideoDescriptor*)d)->aux_video_type = 3;
			gf_list_add(esd->extensionDescriptors, d);
		}
	}
	return esd;
}
