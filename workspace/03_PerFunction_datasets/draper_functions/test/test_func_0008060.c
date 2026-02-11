dump_link_caps(const char *prefix, const char *an_prefix, u32 mask,
	       int link_mode_only)
{
	static const struct {
		int same_line;
		u32 value;
		const char *name;
	} mode_defs[] = {
		{ 0, ADVERTISED_10baseT_Half,       "10baseT/Half" },
		{ 1, ADVERTISED_10baseT_Full,       "10baseT/Full" },
		{ 0, ADVERTISED_100baseT_Half,      "100baseT/Half" },
		{ 1, ADVERTISED_100baseT_Full,      "100baseT/Full" },
		{ 0, ADVERTISED_1000baseT_Half,     "1000baseT/Half" },
		{ 1, ADVERTISED_1000baseT_Full,     "1000baseT/Full" },
		{ 0, ADVERTISED_1000baseKX_Full,    "1000baseKX/Full" },
		{ 0, ADVERTISED_2500baseX_Full,     "2500baseX/Full" },
		{ 0, ADVERTISED_10000baseT_Full,    "10000baseT/Full" },
		{ 0, ADVERTISED_10000baseKX4_Full,  "10000baseKX4/Full" },
		{ 0, ADVERTISED_10000baseKR_Full,   "10000baseKR/Full" },
		{ 0, ADVERTISED_20000baseMLD2_Full, "20000baseMLD2/Full" },
		{ 0, ADVERTISED_20000baseKR2_Full,  "20000baseKR2/Full" },
		{ 0, ADVERTISED_40000baseKR4_Full,  "40000baseKR4/Full" },
		{ 0, ADVERTISED_40000baseCR4_Full,  "40000baseCR4/Full" },
		{ 0, ADVERTISED_40000baseSR4_Full,  "40000baseSR4/Full" },
		{ 0, ADVERTISED_40000baseLR4_Full,  "40000baseLR4/Full" },
	};
	int indent;
	int did1, new_line_pend, i;


	indent = strlen(prefix) + 14;
	if (indent < 24)
		indent = 24;

	fprintf(stdout, "	%s link modes:%*s", prefix,
		indent - (int)strlen(prefix) - 12, "");
	did1 = 0;
	new_line_pend = 0;
	for (i = 0; i < ARRAY_SIZE(mode_defs); i++) {
		if (did1 && !mode_defs[i].same_line)
			new_line_pend = 1;
		if (mask & mode_defs[i].value) {
			if (new_line_pend) {
				fprintf(stdout, "\n");
				fprintf(stdout, "	%*s", indent, "");
				new_line_pend = 0;
			}
			did1++;
			fprintf(stdout, "%s ", mode_defs[i].name);
		}
	}
	if (did1 == 0)
		 fprintf(stdout, "Not reported");
	fprintf(stdout, "\n");

	if (!link_mode_only) {
		fprintf(stdout, "	%s pause frame use: ", prefix);
		if (mask & ADVERTISED_Pause) {
			fprintf(stdout, "Symmetric");
			if (mask & ADVERTISED_Asym_Pause)
				fprintf(stdout, " Receive-only");
			fprintf(stdout, "\n");
		} else {
			if (mask & ADVERTISED_Asym_Pause)
				fprintf(stdout, "Transmit-only\n");
			else
				fprintf(stdout, "No\n");
		}

		fprintf(stdout, "	%s auto-negotiation: ", an_prefix);
		if (mask & ADVERTISED_Autoneg)
			fprintf(stdout, "Yes\n");
		else
			fprintf(stdout, "No\n");
	}
}
