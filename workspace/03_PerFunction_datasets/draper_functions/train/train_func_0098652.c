HEVC_RewriteESDescriptor(GF_MPEGVisualSampleEntryBox *hevc)
{
	if (hevc->emul_esd) gf_odf_desc_del((GF_Descriptor *)hevc->emul_esd);
	hevc->emul_esd = gf_odf_desc_esd_new(2);
	hevc->emul_esd->decoderConfig->streamType = GF_STREAM_VISUAL;
	hevc->emul_esd->decoderConfig->objectTypeIndication = GPAC_OTI_VIDEO_HEVC;
	if (hevc->bitrate) {
		hevc->emul_esd->decoderConfig->bufferSizeDB = hevc->bitrate->bufferSizeDB;
		hevc->emul_esd->decoderConfig->avgBitrate = hevc->bitrate->avgBitrate;
		hevc->emul_esd->decoderConfig->maxBitrate = hevc->bitrate->maxBitrate;
	}
	if (hevc->descr) {
		u32 i=0;
		GF_Descriptor *desc,*clone;
		i=0;
		while ((desc = (GF_Descriptor *)gf_list_enum(hevc->descr->descriptors, &i))) {
			clone = NULL;
			gf_odf_desc_copy(desc, &clone);
			if (gf_odf_desc_add_desc((GF_Descriptor *)hevc->emul_esd, clone) != GF_OK)
				gf_odf_desc_del(clone);
		}
	}
	if (hevc->hevc_config && hevc->hevc_config->config) {
		gf_odf_hevc_cfg_write(hevc->hevc_config->config, &hevc->emul_esd->decoderConfig->decoderSpecificInfo->data, &hevc->emul_esd->decoderConfig->decoderSpecificInfo->dataLength);
	}
}
