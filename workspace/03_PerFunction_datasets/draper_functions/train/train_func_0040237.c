gf_sg_get_namespace_code(GF_SceneGraph *sg, char *qname)
{
	GF_XMLNS *ns;
	u32 i, count;
	count = sg->ns ? gf_list_count(sg->ns) : 0;
	for (i=0; i<count; i++) {
		ns = gf_list_get(sg->ns, i);
		if (!ns->qname && !qname)
			return ns->xmlns_id;

		if (ns->qname && qname && !strcmp(ns->qname, qname))
			return ns->xmlns_id;
	}
	if (qname) {
		if (!strcmp(qname, "xml")) return GF_XMLNS_XML;

	}
	return GF_XMLNS_UNDEFINED;
}
