IntroCharTypeOf(std::istream::int_type ch)
	{
		if (std::istream::traits_type::eof() == ch) {
			return uictOther;
		}

		switch (ch) {
		case 0: return uict00;
		case 0xBB: return uictBB;
		case 0xBF: return uictBF;
		case 0xEF: return uictEF;
		case 0xFE: return uictFE;
		case 0xFF: return uictFF;
		}

		if ((ch > 0) && (ch < 0xFF)) {
			return uictAscii;
		}

		return uictOther;
	}
