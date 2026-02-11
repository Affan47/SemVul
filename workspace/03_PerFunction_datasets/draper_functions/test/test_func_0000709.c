XmtLookupSymbol(StringConst name)
#else
XmtSymbol XmtLookupSymbol(name)
StringConst name;
#endif
{
    XmtSymbol s;
    XrmQuark q = XrmStringToQuark(name);

    if (!symbol_table) return NULL;
    if (XmtHashTableLookup(symbol_table,(XtPointer)q, (XtPointer *)&s))
	return s;
    else
	return NULL;
}
