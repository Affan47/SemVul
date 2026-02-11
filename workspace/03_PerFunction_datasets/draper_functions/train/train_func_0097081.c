ConvertFilename(fstring& str)
	{
		FUStringBuilder xmlBuilder;
		const fchar* s = str.c_str();
		fchar c;
		for (; (c = *s) != 0; ++s)
		{
			if (filenameValidityTable[(uint8) c]) xmlBuilder.append(c);
			else
			{
				xmlBuilder.append((fchar) '%');
				xmlBuilder.appendHex((uint8) c);
			}
		}
		str = xmlBuilder.ToString();
	}
