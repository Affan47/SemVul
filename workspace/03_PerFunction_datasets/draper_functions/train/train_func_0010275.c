cms_get0_revocation_choices(CMS_ContentInfo *cms)
	{
	switch (OBJ_obj2nid(cms->contentType))
		{

		case NID_pkcs7_signed:
		return &cms->d.signedData->crls;

		case NID_pkcs7_enveloped:
		return &cms->d.envelopedData->originatorInfo->crls;

		default:
		CMSerr(CMS_F_CMS_GET0_REVOCATION_CHOICES,
					CMS_R_UNSUPPORTED_CONTENT_TYPE);
		return NULL;

		}
	}
