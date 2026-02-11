refVarRec(char *def)
#else
refVarRec(def)
char *def;
#endif
{
	RefVarRec *p;
	char *s,*decl;

	p = (RefVarRec *) calloc(1, sizeof(RefVarRec));
	require(p!=NULL, "newRefVarRec: no memory");


	s = def;
	while ( isalpha(*s) ) s++;
	if ( strncmp(def, "static", s-def)==0 ) p->global = 1;
	else s = def;


	decl = s;
	while ( *s!='=' && *s!='\0' ) s++;
	if ( *s=='=' ) {

		strcpy(p->init, s+1);
		*s='\0';
	}
	strcpy(p->decl, decl);
	strcpy(p->var, id_in_decl(decl));
	return p;
}
