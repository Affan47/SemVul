makeCssSimpleTag( vString *name, cssKind kind, boolean delete )
{
	vStringTerminate (name);
	makeSimpleTag (name, CssKinds, kind);
	vStringClear (name);
	if( delete )
		vStringDelete (name);
}
