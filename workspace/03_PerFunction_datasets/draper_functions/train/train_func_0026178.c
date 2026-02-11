outputg(){
	int i,j;
	static char format[20];
	static char inf_string[20];
	sprintf(format,"%%%dd",width);
	sprintf(inf_string,"%%%ds",width);
	for(i=0;i<g_size;i++){
		for(j=0;j<g_size;j++)
			if( g[i][j] == INFINITE )
				printf(inf_string,"-");
			else printf(format,g[i][j]);
		printf("\n");
	}
}
