generateText(sk,c)
String sk;
Class  c; {
    String cname = textToStr(cclass(c).text);
    char buffer[MAX_GEN+1];

    if ((strlen(sk)+strlen(cname))>=MAX_GEN) {
	ERRMSG(0) "Please use a shorter name for class \"%s\"", cname
	EEND;
    }
    sprintf(buffer,sk,cname);
    return findText(buffer);
}
