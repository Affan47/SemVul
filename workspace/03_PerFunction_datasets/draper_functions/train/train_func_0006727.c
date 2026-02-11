graphAttrs(FILE * gxlFile, Agraph_t * g)
{
    char *val;

    val = agget(g, GXL_ROLE);
    if (!EMPTY(val)) {
	fprintf(gxlFile, " role=\"%s\"", xml_string(val));
    }
    val = agget(g, GXL_HYPER);
    if (!EMPTY(val)) {
	fprintf(gxlFile, " hypergraph=\"%s\"", xml_string(val));
    }
}
