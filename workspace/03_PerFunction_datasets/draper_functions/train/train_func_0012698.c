DumpBool(FILE *trace, const char *attName, u32  val, u32 indent, Bool XMTDump)
{
	if (!val) return;

	StartAttribute(trace, attName, indent, XMTDump);
	fprintf(trace, "%s", val ? "true" : "false");
	EndAttribute(trace, indent, XMTDump);
}
