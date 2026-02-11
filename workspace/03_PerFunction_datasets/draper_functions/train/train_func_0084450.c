ExpandAllInPlace(const PropSetSimple &props, std::string &withVars, int maxExpands, const VarChain &blankVars) {
	size_t varStart = withVars.find("$(");
	while ((varStart != std::string::npos) && (maxExpands > 0)) {
		size_t varEnd = withVars.find(")", varStart+2);
		if (varEnd == std::string::npos) {
			break;
		}


		size_t innerVarStart = withVars.find("$(", varStart+2);
		while ((innerVarStart != std::string::npos) && (innerVarStart > varStart) && (innerVarStart < varEnd)) {
			varStart = innerVarStart;
			innerVarStart = withVars.find("$(", varStart+2);
		}

		std::string var(withVars.c_str(), varStart + 2, varEnd - varStart - 2);
		std::string val = props.Get(var.c_str());

		if (blankVars.contains(var.c_str())) {
			val = "";
		}

		if (--maxExpands >= 0) {
			maxExpands = ExpandAllInPlace(props, val, maxExpands, VarChain(var.c_str(), &blankVars));
		}

		withVars.erase(varStart, varEnd-varStart+1);
		withVars.insert(varStart, val.c_str(), val.length());

		varStart = withVars.find("$(");
	}

	return maxExpands;
}
