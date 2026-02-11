handleShortOpt(const char* optName) {

		char optn[2];
		optn[1] = '\0';
		SharedOptPtr o;
		while (*optName) {
			optn[0]         = *optName;
			const char* val = optName + 1;
			if ( (o = getOption(optn, OptionContext::find_alias)).get() ) {
				if (o->value()->isImplicit()) {

					if (!o->value()->isFlag()) {

						addOptionValue(o, val);
						return true;
					}
					else {

						addOptionValue(o, "");
						++optName;
					}
				}
				else if (*val != 0 || (val = next()) != 0) {

					addOptionValue(o, val);
					return true;
				}
				else {
					throw SyntaxError(SyntaxError::missing_value, optn);
				}
			}
			else {
				return false;
			}
		}
		return true;
	}
