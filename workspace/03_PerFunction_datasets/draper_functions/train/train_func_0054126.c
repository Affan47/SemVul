commifyr(char* p, Bytebuffer* buf)
{
    int comma = 0;
    int c;
    while((c=*p++)) {
	if(c == ' ') continue;
	if(c == ',') continue;
	else if(c == '}') break;
	if(comma) bbCat(buf,", "); else comma=1;
	if(c == '{') {
	    bbAppend(buf,'{');
	    p = commifyr(p,buf);
	    bbAppend(buf,'}');
	} else if(c == '\'' || c == '\"') {
	    p = wordstring(p,buf,c);
	} else {
	    bbAppend(buf,c);
	    p=word(p,buf);
	}
    }
    return p;
}
