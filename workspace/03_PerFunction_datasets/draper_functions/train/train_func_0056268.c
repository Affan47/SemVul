m_Format(Object *in, Object *out)
{
    char *cp;

    out[0] = NULL;

    if (!in[0]) {
	DXSetError(ERROR_BAD_PARAMETER, "#10000", "template string");
	return ERROR;
    }

    if (!DXExtractString(in[0], &cp)) {
	DXSetError(ERROR_BAD_PARAMETER, "#10200", "template");
	return ERROR;
    }


    out[0] = (Object)format_one(in+1, cp);

    return (out[0] ? OK : ERROR);
}
