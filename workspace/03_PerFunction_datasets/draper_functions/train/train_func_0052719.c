makeFunctionTag (vString *const function,
	vString *const parent, int is_class_parent, const char *arglist __unused__)
{
	tagEntryInfo tag;
	initTagEntry (&tag, vStringValue (function));

	tag.kindName = "function";
	tag.kind = 'f';


	if (vStringLength (parent) > 0)
	{
		if (is_class_parent)
		{
			tag.kindName = "member";
			tag.kind = 'm';
			tag.extensionFields.scope [0] = "class";
			tag.extensionFields.scope [1] = vStringValue (parent);
		}
		else
		{
			tag.extensionFields.scope [0] = "function";
			tag.extensionFields.scope [1] = vStringValue (parent);
		}
	}


	if (strncmp (vStringValue (function), "__", 2) == 0 &&
		strcmp (vStringValue (function), "__init__") != 0)
	{
		tag.extensionFields.access = "private";
		tag.isFileScope = TRUE;
	}
	else
	{
		tag.extensionFields.access = "public";
	}
	makeTagEntry (&tag);
}
