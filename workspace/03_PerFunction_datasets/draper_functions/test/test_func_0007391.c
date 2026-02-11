get_security_action (int val) {
	static char buf [32];

	switch (val) {
	case SECURITY_ACTION_DEMAND:
		return "Demand";
	case SECURITY_ACTION_ASSERT:
		return "Assert";
	case SECURITY_ACTION_DENY:
		return "Deny";
	case SECURITY_ACTION_PERMITONLY:
		return "PermitOnly";
	case SECURITY_ACTION_LINKDEMAND:
		return "LinkDemand";
	case SECURITY_ACTION_INHERITDEMAND:
		return "InheritanceDemand";
	case SECURITY_ACTION_REQMIN:
		return "RequestMinimum";
	case SECURITY_ACTION_REQOPT:
		return "RequestOptional";
	case SECURITY_ACTION_REQREFUSE:
		return "RequestRefuse";

	case SECURITY_ACTION_NONCASDEMAND:
		return "NonCasDemand";
	case SECURITY_ACTION_NONCASLINKDEMAND:
		return "NonCasLinkDemand";
	case SECURITY_ACTION_NONCASINHERITANCE:
		return "NonCasInheritance";

	case SECURITY_ACTION_LINKDEMANDCHOICE:
		return "LinkDemandChoice";
	case SECURITY_ACTION_INHERITDEMANDCHOICE:
		return "InheritanceDemandChoice";
	case SECURITY_ACTION_DEMANDCHOICE:
		return "DemandChoice";
	default:
		g_snprintf (buf, sizeof (buf), "0x%04X", val);
		return buf;
	}
}
