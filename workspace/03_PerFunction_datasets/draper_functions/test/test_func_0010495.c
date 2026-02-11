asn1_template_clear(ASN1_VALUE **pval, const ASN1_TEMPLATE *tt)
	{

	if (tt->flags & (ASN1_TFLG_ADB_MASK|ASN1_TFLG_SK_MASK))
		*pval = NULL;
	else
		asn1_item_clear(pval, ASN1_ITEM_ptr(tt->item));
	}
