makeTclTag (
		const unsigned char *cp,
		vString *const name,
		const tclKind kind)
{
	vStringClear (name);
	while ((int) *cp != '\0'  &&  ! isspace ((int) *cp))
	{
		vStringPut (name, (int) *cp);
		++cp;
	}
	vStringTerminate (name);
	makeSimpleTag (name, TclKinds, kind);
	return cp;
}
