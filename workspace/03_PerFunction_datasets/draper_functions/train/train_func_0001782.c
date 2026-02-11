graph_symbol_to_ascii(struct graph_symbol *symbol)
{
	if (symbol->commit) {
		if (symbol->boundary)
			return " o";
		else if (symbol->initial)
			return " I";
		else if (symbol->merge)
			return " M";
		return " *";
	}

	if (symbol->merge) {
		if (symbol->branch)
			return "-+";
		return "-.";
	}

	if (symbol->branch) {
		if (symbol->branched) {
			if (symbol->vbranch)
				return "-+";
			return "-'";
		}
		if (symbol->vbranch)
			return "-|";
		return " |";
	}

	if (symbol->vbranch)
		return "--";

	return "  ";
}
