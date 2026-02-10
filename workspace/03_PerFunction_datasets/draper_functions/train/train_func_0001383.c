ParseAOCDSpecificChargingUnits(struct Aoc *chanp, u_char *p, u_char *end, int dummy)
{
	int recordedUnits;
	int typeOfChargingInfo;
	int billingId;
	INIT;

	XSEQUENCE_1(ParseRecordedUnitsList, ASN1_TAG_SEQUENCE, 1, &recordedUnits);
	XSEQUENCE_1(ParseTypeOfChargingInfo, ASN1_TAG_ENUM, 2, &typeOfChargingInfo);
	XSEQUENCE_OPT_1(ParseAOCDBillingId, ASN1_TAG_ENUM, 3, &billingId);

	chanp->type_of_charging_info = typeOfChargingInfo;
	chanp->amount = recordedUnits;

	return p - beg;
}
