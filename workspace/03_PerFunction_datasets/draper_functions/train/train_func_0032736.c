oclinearize(OCtype etype, unsigned int nstrings, char** strings)
{
    int i;
    size_t typesize;
    char* memp;
    char* memory;

    if(nstrings == 0) return NULL;
    typesize = octypesize(etype);
    memory = (char*)ocmalloc(nstrings*typesize);
    MEMCHECK(memory,NULL);
    memp = memory;
    for(i=0;i<nstrings;i++) {
	char* value = strings[i];
        converttype(etype,value,memp);
	memp += typesize;
    }
    return memory;
}
