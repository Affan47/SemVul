WriteGF_IPMPX_AUTH(GF_BitStream *bs, GF_IPMPX_Authentication *auth)
{
	u32 size;

	if (!auth) return GF_OK;
	gf_bs_write_int(bs, auth->tag, 8);

	size = GF_IPMPX_AUTH_Size(auth);
	write_var_size(bs, size);

	switch (auth->tag) {
	case GF_IPMPX_AUTH_AlgorithmDescr_Tag:
		{
			GF_IPMPX_AUTH_AlgorithmDescriptor *p = (GF_IPMPX_AUTH_AlgorithmDescriptor *)auth;
			gf_bs_write_int(bs, p->specAlgoID ? 0 : 1, 1);
			gf_bs_write_int(bs, 0, 7);
			if (p->specAlgoID) {
				GF_IPMPX_WriteByteArray(bs, p->specAlgoID);
			} else {
				gf_bs_write_int(bs, p->regAlgoID, 16);
			}
			GF_IPMPX_WriteByteArray(bs, p->OpaqueData);
		}
		break;
	case GF_IPMPX_AUTH_KeyDescr_Tag:
		{
			GF_IPMPX_AUTH_KeyDescriptor *p = (GF_IPMPX_AUTH_KeyDescriptor *)auth;

			gf_bs_write_data(bs, p->keyBody, p->keyBodyLength);
		}
		break;
	default:
		break;
	}
	return GF_OK;
}
