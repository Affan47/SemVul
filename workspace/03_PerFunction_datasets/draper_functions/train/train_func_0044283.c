lowercase(const char* str)
{
    char* p = 0;
    char* new = strdup(str);

    if(str ==0){
	return 0;
    }

    for(p = new; *p!=0; p++){
	*p = tolower(*p);
    }

    return new;
}
