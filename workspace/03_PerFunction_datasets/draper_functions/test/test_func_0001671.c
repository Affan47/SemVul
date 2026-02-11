parse_function (xmlNode *node, const gchar *parent)
{
	xmlNode *i, *k;
	gchar *name;
	tagEntryInfo *tag;

	g_assert (node != NULL);

	name = (gchar*)xmlGetProp (node, (xmlChar*)"name");
	if (!name)
		return;

	tag = (tagEntryInfo*)malloc (sizeof (tagEntryInfo));
	initTagEntry (tag, name);
	get_file_pos (node->line, &tag->filePosition, File.fp);
	tag->lineNumber = node->line;
	tag->isFileScope	= 1;
	tag->kindName = "function";
	tag->kind = 'f';
	if (parent) {
		tag->kindName = "member";
		tag->kind = 'm';
		tag->extensionFields.scope[0] = "class";
		tag->extensionFields.scope[1] = parent;
	}

	for (i = node->children; i; i = i->next)
	{
		if (!i->name)
			continue;
		if (strcmp ((const gchar*)i->name, "return-value") == 0)
		{
			for (k = i->children; k; k = k->next)
			{
				const gchar *tmp;
				if (!k->name)
					continue;
				tmp = (const gchar*)xmlGetProp (k, (const xmlChar*)"name");
				if (!tmp)
					continue;
				tag->extensionFields.returnType = tmp;
			}
		}
		if (strcmp ((const gchar*)i->name, "parameters") == 0)
		{
			for (k = i->children; k; k = k->next)
			{


			}
		}
	}
	makeTagEntry (tag);
}
