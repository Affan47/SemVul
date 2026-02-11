computeAreaForQuery(icp)
IMIC *icp;
{
    IMPSAttributes *pattr = &icp->preedit_attr;
    IMPSAttributes *sattr = &icp->status_attr;

    TRACE(("computeAreaForQuery()\n"));

    if (icp->style == IMSTYLE_SEPARATE) return;

    computeAreaNeeded(icp);

    if (!(pattr->set_mask & ATTR_MASK_AREA)) {
	if (icp->style == IMSTYLE_OVER_THE_SPOT) {
	    IMWindowProfile *fpr = &icp->focus_profile;

	    pattr->area.x = 0;
	    pattr->area.y = 0;
	    pattr->area.width = fpr->width;
	    pattr->area.height = fpr->height;
	} else {
	    pattr->area = pattr->area_needed;
	}
    }

    if (!(sattr->set_mask & ATTR_MASK_AREA)) {
	sattr->area = sattr->area_needed;
    }
}
