computeAreaNeeded(icp)
IMIC *icp;
{
    IMPSAttributes *pattr = &icp->preedit_attr;
    IMPSAttributes *sattr = &icp->status_attr;
    IMWindowProfile *cpr = &icp->client_profile;
    int width, height;
    int min_width, min_height;
    int default_status_width;
    int font_height;

    TRACE(("computeAreaNeeded()\n"));

    if (icp->style == IMSTYLE_SEPARATE) return;


    (void)validateClientWindow(icp);


    fillPSDefault(icp, NEST_STATUS, (unsigned long)ATTR_MASK_LINESPACE);
    font_height = sattr->line_space + 2;
    width = height = 0;
    if (sattr->set_mask & ATTR_MASK_AREA_NEEDED) {
	width = sattr->area_needed.width;
	height = sattr->area_needed.height;
	TRACE(("\tstatus areaNeeded was: (%d,%d)\n", width, height));
    }

    min_width = font_height * 3;
    min_height = font_height;
    if (min_width < MIN_AREA_WIDTH) min_width = MIN_AREA_WIDTH;
    if (min_height < MIN_AREA_HEIGHT) min_height = MIN_AREA_HEIGHT;

    if (width == 0) {
	default_status_width =
	    IMStatusWidth(icp->im->connection->proto_widget);
	if (default_status_width > 0) {
	    width = default_status_width;
	} else {
	    width = cpr->width / 5;
	}
    }

    if (width < min_width) width = min_width;
    if (height < min_height) height = min_height;

    sattr->area_needed.x = 0;
    sattr->area_needed.y = cpr->height - height;
    sattr->area_needed.width = width;
    sattr->area_needed.height = height;
    TRACE(("\tstatus areaNeeded is now: (%d, %d, %d, %d)\n",
	    sattr->area_needed.x, sattr->area_needed.y, width, height));


    if (icp->style != IMSTYLE_OFF_THE_SPOT) return;

    fillPSDefault(icp, NEST_PREEDIT, (unsigned long)ATTR_MASK_LINESPACE);
    font_height = pattr->line_space + 2;
    width = height = 0;
    if (pattr->set_mask & ATTR_MASK_AREA_NEEDED) {
	width = pattr->area_needed.width;
	height = pattr->area_needed.height;
	TRACE(("\tpreedit areaNeeded was: (%d,%d)\n",
		width, height));
    }

    min_width = (cpr->width - sattr->area_needed.width) / 2;
    min_height = font_height;
    if (min_width < MIN_AREA_WIDTH) min_width = MIN_AREA_WIDTH;
    if (min_height < MIN_AREA_HEIGHT) min_height = MIN_AREA_HEIGHT;

    if (width < min_width) width = min_width;
    if (height < min_height) height = min_height;

    pattr->area_needed.x = sattr->area_needed.width;
    pattr->area_needed.y = cpr->height - height;
    pattr->area_needed.width = width;
    pattr->area_needed.height = height;
    TRACE(("\tpreedit areaNeeded is now: (%d, %d, %d, %d)\n",
	    pattr->area_needed.x, pattr->area_needed.y, width, height));
}
