gn_calnote_recurrence2str(gn_calnote_recurrence r)
{
	switch (r) {
	case GN_CALNOTE_NEVER:	return _("Never");
	case GN_CALNOTE_DAILY:	return _("Daily");
	case GN_CALNOTE_WEEKLY:	return _("Weekly");
	case GN_CALNOTE_2WEEKLY:return _("Every 2 weeks");
	case GN_CALNOTE_MONTHLY:return _("Monthly");
	case GN_CALNOTE_YEARLY:	return _("Yearly");
	default:		return _("Unknown");
	}
}
