ReadGF_IPMPX_TrustSecurityMetadata(GF_BitStream *bs, GF_IPMPX_Data *_p, u32 size)
{
	u32 nbTools, nbSpec;
	GF_IPMPX_TrustSecurityMetadata *p = (GF_IPMPX_TrustSecurityMetadata *)_p;
	nbTools = gf_bs_read_int(bs, 16);
	while (nbTools) {
		GF_IPMPX_TrustedTool *tt = (GF_IPMPX_TrustedTool *)gf_malloc(sizeof(GF_IPMPX_TrustedTool));
		if (!tt) return GF_OUT_OF_MEM;
		memset(tt, 0, sizeof(GF_IPMPX_TrustedTool));
		tt->tag = GF_IPMPX_TRUSTED_TOOL_TAG;
		nbTools--;
		gf_list_add(p->TrustedTools, tt);
		gf_bs_read_data(bs, (char*)tt->toolID, 16);
		gf_bs_read_data(bs, tt->AuditDate, 5);
		tt->trustSpecifications = gf_list_new();
		nbSpec = gf_bs_read_int(bs, 16);
		while (nbSpec) {
			Bool has_cc;
			GF_IPMPX_TrustSpecification *tts = (GF_IPMPX_TrustSpecification *)gf_malloc(sizeof(GF_IPMPX_TrustSpecification));
			if (!tts) return GF_OUT_OF_MEM;
			memset(tts, 0, sizeof(GF_IPMPX_TrustSpecification));
			tts->tag = GF_IPMPX_TRUST_SPECIFICATION_TAG;
			nbSpec--;
			gf_list_add(tt->trustSpecifications, tts);
			has_cc = gf_bs_read_int(bs, 1);
			gf_bs_read_int(bs, 7);
			if (has_cc) {
				tts->CCTrustMetadata = GF_IPMPX_GetByteArray(bs);
			} else {
				gf_bs_read_data(bs, tts->startDate, 5);
				tts->attackerProfile = gf_bs_read_int(bs, 2);
				gf_bs_read_int(bs, 6);
				tts->trustedDuration = gf_bs_read_int(bs, 32);
			}
		}
	}
	return GF_OK;
}
