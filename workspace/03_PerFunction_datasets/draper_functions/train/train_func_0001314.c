printLpStats(const PreproStats& lp) const {
	printKeyValue("Atoms", "%-6u", lp.atoms);
	if (lp.trStats) {
		printf(" (Original: %u Auxiliary: %u)", lp.atoms-lp.trStats->auxAtoms, lp.trStats->auxAtoms);
	}
	printf("\n");
	printKeyValue("Rules", "%-6u", lp.rules[0]);
	printf(" (1: %u", lp.rules[BASICRULE] - (lp.trStats?lp.trStats->rules[0]:0));
	if (lp.trStats) { printf("/%u", lp.rules[BASICRULE]); }
	for (int i = 2; i <= OPTIMIZERULE; ++i) {
		if (lp.rules[i] > 0) {
			printf(" %d: %u", i, lp.rules[i]);
			if (lp.trStats) { printf("/%u", lp.rules[i]-lp.trStats->rules[i]); }
		}
	}
	printf(")\n");
	printKeyValue("Bodies", "%-6u\n", lp.bodies);
	if (lp.sumEqs() > 0) {
		printKeyValue("Equivalences", "%-6u", lp.sumEqs());
		printf(" (Atom=Atom: %u Body=Body: %u Other: %u)\n"
			, lp.numEqs(Var_t::atom_var)
			, lp.numEqs(Var_t::body_var)
			, lp.numEqs(Var_t::atom_body_var));
	}
	printKey("Tight");
	if      (lp.sccs == 0)               { printf("Yes"); }
	else if (lp.sccs != PrgNode::noScc)  { printf("%-6s (SCCs: %u Nodes: %u)", "No", lp.sccs, lp.ufsNodes); }
	else                                 { printf("N/A"); }
	printf("\n");
}
