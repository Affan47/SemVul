md_arcname(char *name_req) {

    int pos;
    char *newname;

    pos=strlen(name_req);
    if (pos>3 &&
	tolower(name_req[pos-1])=='a' &&
	tolower(name_req[pos-2])=='h' &&
	name_req[pos-3]=='.') return name_req;
    if ((newname=malloc(pos+4))==NULL) error(1,ERR_MEM,"md_arcname()");
    strcpy(newname,name_req);
    strcpy(newname+pos,".ha");
    return newname;
}
