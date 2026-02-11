cst_substr(const char *str,int start, int length)
{
    char *nstr = NULL;

    if (str)
    {
	nstr = cst_alloc(char,length+1);
	strncpy(nstr,str+start,length);
	nstr[length] = '\0';
    }
    return nstr;
}
