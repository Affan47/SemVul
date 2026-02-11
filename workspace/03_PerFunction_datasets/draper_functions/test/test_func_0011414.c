getKerningWidth(const wchar_t* thisLetter=0, const wchar_t* previousLetter=0) const
	{
		s32 ret = GlobalKerningWidth;

		if (thisLetter)
		{
			ret += Areas[getAreaIDFromCharacter(*thisLetter, NULL)].overhang;

			if (previousLetter)
			{
				ret += Areas[getAreaIDFromCharacter(*previousLetter, NULL)].underhang;
			}
		}

		return ret;
	}
