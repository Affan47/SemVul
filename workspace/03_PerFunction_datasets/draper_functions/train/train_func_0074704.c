OCSP_id_get0_info(ASN1_OCTET_STRING **piNameHash, ASN1_OBJECT **pmd,
			ASN1_OCTET_STRING **pikeyHash,
			ASN1_INTEGER **pserial, OCSP_CERTID *cid)
	{
	if (!cid) return 0;
	if (pmd) *pmd = cid->hashAlgorithm->algorithm;
	if(piNameHash) *piNameHash = cid->issuerNameHash;
	if (pikeyHash) *pikeyHash = cid->issuerKeyHash;
	if (pserial) *pserial = cid->serialNumber;
	return 1;
	}
