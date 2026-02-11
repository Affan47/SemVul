ajStrPrefixC(const AjPStr str, const char* txt2)
{
    size_t ilen;

    if(!str)
	return ajFalse;

    ilen = strlen(txt2);

    if(!ilen)
	return ajFalse;

    if(ilen > MAJSTRGETLEN(str))
	return ajFalse;

    if(strncmp(MAJSTRGETPTR(str), txt2, ilen))
	return ajFalse;

    return ajTrue;
}
