default_link_status(int linkFirmId)
{
	int rc;

	switch(firm_id)
	{
		case FIRM_MINE:
			rc = (linkFirmId!=FIRM_MARKET);
			break;

		case FIRM_FACTORY:
			rc = (linkFirmId==FIRM_MARKET) || (linkFirmId==FIRM_MINE);
			break;

		case FIRM_MARKET:
			rc = (linkFirmId==FIRM_FACTORY) || (linkFirmId==FIRM_HARBOR);
			break;

		case FIRM_HARBOR:
			rc = (linkFirmId==FIRM_MARKET) || (linkFirmId==FIRM_MINE) ||
				  (linkFirmId==FIRM_FACTORY);
			break;

		default:
			rc = 1;
	}

	if( rc )
		return LINK_EE;
	else
		return LINK_DD;
}
