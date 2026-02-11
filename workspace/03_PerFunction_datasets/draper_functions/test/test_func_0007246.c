m_Measure(Object *in, Object *out)
{
    char *what;

    out[0] = NULL;

    if (! in[0])
    {
	DXSetError(ERROR_MISSING_DATA, "#10000", "input");
	goto error;
    }

    if (! in[1])
	what = NULL;
    else if (! DXExtractString(in[1], &what))
    {
	DXSetError(ERROR_BAD_PARAMETER, "\"what\" must be a string");
	goto error;
    }

    out[0] = DXMeasure(in[0], what);
    if (! out[0])
	goto error;

    return OK;


error:
    return ERROR;
}
