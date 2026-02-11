token_status( char *str)
{
	int i,j,k,l;
	PARSER p;
	DELIM igualador={ '=','=','=' };
	DELIM separador={ '/',',','/' };

	p.igualador = &igualador;
	p.separador = &separador;

	strncpy(p.sig,str,sizeof(p.sig) );


	j=0;k=0;l=0;
	do{
		i=parser_init( &p );
		if(p.status && j==0)
			l=atoi(p.token);

		else if(p.status && j==1)
			k=atoi(p.token);

		else if(p.status && j==2 ) {
			strncpy(usuario.names[l],p.token,sizeof(usuario.names[l]));
			textfill(0,_("%i [%s] %s"),l,_(estado[k]),p.token);
		}
		j++;
		j=j%3;
	} while(i);
}
