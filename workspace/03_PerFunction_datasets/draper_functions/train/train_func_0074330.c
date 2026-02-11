IsIndexedSlotAttr()
{
	Assert(FitsSymbolType(ksymtSlotAttr));

	if (FieldIs(0, "component") && LastFieldIs("reference"))
		return true;
	else if (IsUserDefinableSlotAttr())
		return true;
	else
		return false;
}
