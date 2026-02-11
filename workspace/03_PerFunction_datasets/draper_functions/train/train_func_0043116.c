makeFunctionTag (vString *const function,
	vString *const parent, int is_class_parent, const char *arglist)
{
	tagEntryInfo tag;
	initTagEntry (&tag, vStringValue (function));

	tag.kindName = PythonKinds[K_FUNCTION].name;
	tag.kind = PythonKinds[K_FUNCTION].letter;
	tag.extensionFields.arglist = arglist;

	if (strcmp (vStringValue (function), "__init__") == 0 && parent != NULL)
	{
		const char *parent_tag_name = get_class_name_from_parent (vStringValue (parent));
		if (parent_tag_name != NULL)
			setTagArglistByName (parent_tag_name, arglist);
	}

	if (vStringLength (parent) > 0)
	{
		if (is_class_parent)
		{
			tag.kindName = PythonKinds[K_METHOD].name;
			tag.kind = PythonKinds[K_METHOD].letter;
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
