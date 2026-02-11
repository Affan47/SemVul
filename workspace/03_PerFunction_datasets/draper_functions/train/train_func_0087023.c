indented(int n)
{
    char* indentation;
    if(dent == NULL) {
	dent = (char*)emalloc(INDENTMAX+1);
	memset((void*)dent,' ',INDENTMAX);
	dent[INDENTMAX] = '\0';
    }
    if(n*4 >= INDENTMAX) n = INDENTMAX/4;
    indentation = dent+(INDENTMAX - 4*n);
    return indentation;
}
