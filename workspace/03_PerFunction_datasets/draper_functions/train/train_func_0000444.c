edgeAttrs(FILE * gxlFile, Agedge_t * e)
{
    char *val;

    val = agget(e, GXL_ID);
    if (!EMPTY(val)) {
	fprintf(gxlFile, " id=\"%s\"", xml_string(val));
    }
    val = agget(e, GXL_FROM);
    if (!EMPTY(val)) {
	fprintf(gxlFile, " fromorder=\"%s\"", xml_string(val));
    }
    val = agget(e, GXL_TO);
    if (!EMPTY(val)) {
	fprintf(gxlFile, " toorder=\"%s\"", xml_string(val));
    }
}
