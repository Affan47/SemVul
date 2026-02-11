UFOGetByteArray(char *array,int cnt,xmlDocPtr doc,xmlNodePtr value) {
    xmlNodePtr kid;
    int i;

    memset(array,0,cnt);

    if ( _xmlStrcmp(value->name,(const xmlChar *) "array")!=0 )
return;
    i=0;
    for ( kid = value->children; kid!=NULL; kid=kid->next ) {
	if ( _xmlStrcmp(kid->name,(const xmlChar *) "integer")==0 ) {
	    char *valName = (char *) _xmlNodeListGetString(doc,kid->children,true);
	    if ( i<cnt )
		array[i++] = strtol(valName,NULL,10);
	    free(valName);
	}
    }
}
