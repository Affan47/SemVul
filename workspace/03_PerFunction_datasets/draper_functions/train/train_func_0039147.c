ajStrFindC(const AjPStr str, const char* txt2)
{
    const char* cp;

    cp = strstr(MAJSTRGETPTR(str), txt2);

    if(!cp)
	return -1;

    return(cp - str->Ptr);
}
