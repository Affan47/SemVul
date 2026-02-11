CountPasses(int * pcpass, int * pcpassLB, int * pcpassSub,
	int * pcpassJust, int * pcpassPos, int * pipassBidi)
{
	GdlRuleTable * prultbl;

	if ((prultbl = FindRuleTable("linebreak")) != NULL)
		*pcpassLB = prultbl->CountPasses();
	else
		*pcpassLB = 0;

	if ((prultbl = FindRuleTable("substitution")) != NULL)
		*pcpassSub = prultbl->CountPasses();
	else
		*pcpassSub = 0;

	if ((prultbl = FindRuleTable("justification")) != NULL)
		*pcpassJust = prultbl->CountPasses();
	else
		*pcpassJust = 0;

	if ((prultbl = FindRuleTable("positioning")) != NULL)
		*pcpassPos = prultbl->CountPasses();
	else
		*pcpassPos = 0;

	*pcpass = *pcpassLB + *pcpassSub + *pcpassJust + *pcpassPos;

	if (Bidi())
		*pipassBidi = *pcpassLB + *pcpassSub;
	else
		*pipassBidi = -1;
}
