gf_ipmpx_dump_ParametricDescription(GF_IPMPX_Data *_p, FILE *trace, u32 indent, Bool XMTDump)
{
	u32 i;
	GF_IPMPX_ParametricDescription*p = (GF_IPMPX_ParametricDescription*)_p;
	StartElement(trace, "IPMP_ParametricDescription", indent, XMTDump);
	indent++;
	DumpInt(trace, "majorVersion", p->majorVersion, indent, XMTDump);
	DumpInt(trace, "minorVersion", p->minorVersion, indent, XMTDump);
	EndAttributes(trace, XMTDump, 1);
	gf_ipmpx_dump_BaseData(_p, trace, indent, XMTDump);
	gf_ipmpx_dump_ByteArray(p->descriptionComment, "descriptionComment", trace, indent, XMTDump);

	StartList(trace, "descriptions", indent, XMTDump);
	indent++;
	for (i=0; i<gf_list_count(p->descriptions); i++) {
		GF_IPMPX_ParametricDescriptionItem *it = (GF_IPMPX_ParametricDescriptionItem *)gf_list_get(p->descriptions, i);
		StartElement(trace, "IPMP_ParametricDescriptionItem", indent, XMTDump);
		indent++;
		EndAttributes(trace, XMTDump, 1);
		gf_ipmpx_dump_ByteArray(it->main_class, "class", trace, indent, XMTDump);
		gf_ipmpx_dump_ByteArray(it->subClass, "subClass", trace, indent, XMTDump);
		gf_ipmpx_dump_ByteArray(it->typeData, "typeData", trace, indent, XMTDump);
		gf_ipmpx_dump_ByteArray(it->type, "type", trace, indent, XMTDump);
		gf_ipmpx_dump_ByteArray(it->addedData, "addedData", trace, indent, XMTDump);
		indent--;
		EndElement(trace, "IPMP_ParametricDescriptionItem", indent, XMTDump);
	}
	indent--;
	EndList(trace, "descriptions", indent, XMTDump);

	indent--;
	EndElement(trace, "IPMP_ParametricDescription", indent, XMTDump);
	return GF_OK;
}
