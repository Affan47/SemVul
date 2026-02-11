makeAbcTag (const vString* const name, boolean name_before)
{
	tagEntryInfo e;
	initTagEntry (&e, vStringValue(name));

	if (name_before)
		e.lineNumber--;
	e.kindName = AbcKinds[0].name;
	e.kind = AbcKinds[0].letter;

	makeTagEntry(&e);
}
