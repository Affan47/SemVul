ajStrFindAnyC(const AjPStr str, const char* txt2)
{
    size_t i;

    i = strcspn(MAJSTRGETPTR(str), txt2);

    if(i == str->Len)
	return -1;

    return i;
}
