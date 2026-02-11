extract_name (const char *begin, const char *end, vString *name)
{
	if (begin != NULL  &&  end != NULL  &&  begin < end)
	{
		const char *cp;

		while (isspace ((int) *begin))
			begin++;
		while (isspace ((int) *end))
			end--;
		if (begin < end)
		{
			for (cp = begin ; cp != end; cp++)
				vStringPut (name, (int) *cp);
			vStringTerminate (name);

			makeSimpleTag (name, LuaKinds, K_FUNCTION);
			vStringClear (name);
		}
	}
}
