gf_odf_dump_cc_name(GF_CC_Name *cnd, FILE *trace, u32 indent, Bool XMTDump)
{
	u32 i;
	GF_ContentCreatorInfo *p;

	StartDescDump(trace, "ContentCreatorNameDescriptor", indent, XMTDump);
	EndAttributes(trace, indent, XMTDump);
	indent++;
	i=0;
	while ((p = (GF_ContentCreatorInfo *)gf_list_enum(cnd->ContentCreators, &i))) {
		StartSubElement(trace, "Creator", indent, XMTDump);
		DumpInt(trace, "languageCode", p->langCode, indent, XMTDump);
		DumpBool(trace, "isUTF8", p->isUTF8, indent, XMTDump);
		DumpString(trace, "Name", p->contentCreatorName, indent, XMTDump);
		EndSubElement(trace, indent, XMTDump);
	}
	indent--;
	EndDescDump(trace, "ContentCreatorNameDescriptor", indent, XMTDump);
	return GF_OK;
}
