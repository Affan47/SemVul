gf_ipmpx_dump_ConnectTool(GF_IPMPX_Data *_p, FILE *trace, u32 indent, Bool XMTDump)
{
	GF_IPMPX_ConnectTool*p = (GF_IPMPX_ConnectTool*)_p;
	StartElement(trace, "IPMP_ConnectTool", indent, XMTDump);
	indent++;
	EndAttributes(trace, XMTDump, 1);
	gf_ipmpx_dump_BaseData(_p, trace, indent, XMTDump);
	if (!XMTDump) StartAttribute(trace, "toolDescriptor", indent, 0);
	else {
		StartElement(trace, "toolDescriptor", indent, XMTDump);
		EndAttributes(trace, XMTDump, 1);
	}
	gf_odf_dump_desc((GF_Descriptor *)p->toolDescriptor, trace, indent, XMTDump);
	if (XMTDump) EndElement(trace, "toolDescriptor", indent, XMTDump);

	indent--;
	EndElement(trace, "IPMP_ConnectTool", indent, XMTDump);
	return GF_OK;
}
