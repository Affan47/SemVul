ignoreCCS (CostCentreStack *ccs)
{
    if (RtsFlags.CcFlags.doCostCentres < COST_CENTRES_ALL &&
        (   ccs == CCS_OVERHEAD
         || ccs == CCS_DONT_CARE
         || ccs == CCS_GC
         || ccs == CCS_SYSTEM
         || ccs == CCS_IDLE)) {
        return rtsTrue;
    } else {
	return rtsFalse;
    }
}
