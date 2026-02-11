doParse() {
		bool breakEarly  = false;
		SharedOptPtr po(0);
		std::string poName, poNameLast;
		const char* curr;
		while ( (curr=next()) && !breakEarly ) {
			switch(getOptionType(curr)) {
				case short_opt: if (handleShortOpt(curr + 1)) curr = 0; break;
				case neg_opt :  if (handleNegOpt(curr+5)) { curr = 0; break; }
				case long_opt:  if (handleLongOpt(curr + 2)) curr = 0;  break;
				case end_opt:   curr = 0; breakEarly = true; break;
				case no_opt:
				if (!posOpt_ || !posOpt_(curr, poName)) {
					po = getOption("Positional Option", OptionContext::find_name_or_prefix);
				}
				else if (poName != poNameLast) {
					po = getOption(poName.c_str(), OptionContext::find_name_or_prefix);
					poNameLast = poName;
				}
				if (po.get())  {
					addOptionValue(po, curr);
					curr = 0;
				}
				break;
				default:
					assert(0);
			}
			if (curr) {
				remaining.push_back(curr);
			}
		}
		while (curr)  {
			remaining.push_back(curr);
			curr = next();
		}
	}
