ParseAOCDSpecificCurrency(struct Aoc *chanp, u_char *p, u_char *end, int dummy)
{
	int typeOfChargingInfo;
	int billingId;
	INIT;

	XSEQUENCE(ParseRecordedCurrency, ASN1_TAG_SEQUENCE, 1);
	XSEQUENCE_1(ParseTypeOfChargingInfo, ASN1_TAG_ENUM, 2, &typeOfChargingInfo);
	XSEQUENCE_OPT_1(ParseAOCDBillingId, ASN1_TAG_ENUM, 3, &billingId);

	return p - beg;
}
