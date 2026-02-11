FcParseMatch (FcConfigParse *parse)
{
    const FcChar8   *kind_name;
    FcMatchKind	    kind;
    FcTest	    *test = 0;
    FcEdit	    *edit = 0;
    FcVStack	    *vstack;
    FcBool           tested = FcFalse;
    FcSubstStack    *sstack = NULL;
    int              len, pos = 0;

    kind_name = FcConfigGetAttribute (parse, "target");
    if (!kind_name)
	kind = FcMatchPattern;
    else
    {
	if (!strcmp ((char *) kind_name, "pattern"))
	    kind = FcMatchPattern;
	else if (!strcmp ((char *) kind_name, "font"))
	    kind = FcMatchFont;
	else if (!strcmp ((char *) kind_name, "scan"))
	    kind = FcMatchScan;
	else
	{
	    FcConfigMessage (parse, FcSevereWarning, "invalid match target \"%s\"", kind_name);
	    return;
	}
    }
    len = FcVStackElements(parse);
    if (len > 0)
    {
	sstack = malloc (sizeof (FcSubstStack) * (len + 1));
	if (!sstack)
	{
	    FcConfigMessage (parse, FcSevereError, "out of memory");
	    return;
	}
    }
    while ((vstack = FcVStackPeek (parse)))
    {
	switch ((int) vstack->tag) {
	case FcVStackTest:
	    vstack->u.test->next = test;
	    test = vstack->u.test;
	    vstack->tag = FcVStackNone;
	    tested = FcTrue;
	    break;
	case FcVStackEdit:


	    if (tested)
	    {
		sstack[pos].test = test;
		sstack[pos].edit = edit;
		pos++;
		test = NULL;
		edit = NULL;
		tested = FcFalse;
	    }
	    vstack->u.edit->next = edit;
	    edit = vstack->u.edit;
	    vstack->tag = FcVStackNone;
	    if (kind == FcMatchScan && edit->object > FC_MAX_BASE_OBJECT)
	    {
		FcConfigMessage (parse, FcSevereError,
				 "<match target=\"scan\"> cannot edit user-defined object \"%s\"",
				 FcObjectName(edit->object));
	    }
	    break;
	default:
	    FcConfigMessage (parse, FcSevereWarning, "invalid match element");
	    break;
	}
	FcVStackPopAndDestroy (parse);
    }
    if (!FcConfigAddEdit (parse->config, test, edit, kind))
	FcConfigMessage (parse, FcSevereError, "out of memory");
    if (sstack)
    {
	int i;

	for (i = 0; i < pos; i++)
	{
	    if (!FcConfigAddEdit (parse->config, sstack[pos - i - 1].test, sstack[pos - i - 1].edit, kind))
	    {
		FcConfigMessage (parse, FcSevereError, "out of memory");
		return;
	    }
	}
	free (sstack);
    }
}
