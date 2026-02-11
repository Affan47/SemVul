gf_isom_set_ismacryp_protection(GF_ISOFile *the_file, u32 trackNumber, u32 desc_index, u32 scheme_type,
						   u32 scheme_version, char *scheme_uri, char *kms_URI,
						   Bool selective_encryption, u32 KI_length, u32 IV_length)
{
	u32 original_format;
	GF_Err e;
	GF_SampleEntryBox *sea;
	GF_ProtectionInfoBox *sinf;
	GF_TrackBox *trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (!trak) return GF_BAD_PARAM;

	e = Media_GetSampleDesc(trak->Media, desc_index, &sea, NULL);
	if (e) return e;


	switch (sea->type) {
	case GF_ISOM_BOX_TYPE_MP4A:
	case GF_ISOM_BOX_TYPE_DAMR:
	case GF_ISOM_BOX_TYPE_DEVC:
	case GF_ISOM_BOX_TYPE_DQCP:
	case GF_ISOM_BOX_TYPE_DSMV:
	case GF_ISOM_BOX_TYPE_AC3:
		original_format = sea->type;
		sea->type = GF_ISOM_BOX_TYPE_ENCA;
		break;
	case GF_ISOM_BOX_TYPE_MP4V:
	case GF_ISOM_BOX_TYPE_D263:
		original_format = sea->type;
		sea->type = GF_ISOM_BOX_TYPE_ENCV;
		break;

	case GF_ISOM_BOX_TYPE_AVC1:
	case GF_ISOM_BOX_TYPE_AVC2:
	case GF_ISOM_BOX_TYPE_AVC3:
	case GF_ISOM_BOX_TYPE_AVC4:
	case GF_ISOM_BOX_TYPE_SVC1:
		original_format = GF_4CC('2','6','4','b');
		sea->type = GF_ISOM_BOX_TYPE_ENCV;
		break;
	case GF_ISOM_BOX_TYPE_HVC1:
	case GF_ISOM_BOX_TYPE_HEV1:
		original_format = GF_4CC('2','6','5','b');
		sea->type = GF_ISOM_BOX_TYPE_ENCV;
		break;
	case GF_ISOM_BOX_TYPE_MP4S:
	case GF_ISOM_BOX_TYPE_LSR1:
		original_format = sea->type;
		sea->type = GF_ISOM_BOX_TYPE_ENCS;
		break;
	default:
		return GF_BAD_PARAM;
	}

	sinf = (GF_ProtectionInfoBox *)sinf_New();
	gf_list_add(sea->protections, sinf);

	sinf->scheme_type = (GF_SchemeTypeBox *)schm_New();
	sinf->scheme_type->scheme_type = scheme_type;
	sinf->scheme_type->scheme_version = scheme_version;
	if (scheme_uri) {
		sinf->scheme_type->flags |= 0x000001;
		sinf->scheme_type->URI = gf_strdup(scheme_uri);
	}
	sinf->original_format = (GF_OriginalFormatBox *)frma_New();
	sinf->original_format->data_format = original_format;
	sinf->info = (GF_SchemeInformationBox *)schi_New();

	sinf->info->ikms = (GF_ISMAKMSBox *)iKMS_New();
	sinf->info->ikms->URI = gf_strdup(kms_URI);

	sinf->info->isfm = (GF_ISMASampleFormatBox *)iSFM_New();
	sinf->info->isfm->selective_encryption = selective_encryption;
	sinf->info->isfm->key_indicator_length = KI_length;
	sinf->info->isfm->IV_length = IV_length;
	return GF_OK;
}
