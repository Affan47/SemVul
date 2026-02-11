itemdb_read_itemavail(void)
{
	FILE *fp;
	char line[1024];
	int ln=0;
	int nameid,j,k;
	char *str[2],*p;
	const char *filename = "db/item_avail.txt";

	if( (fp = fopen(filename, "r")) == NULL ) {
		printf("itemdb_read_itemavail: open [%s] failed !\n", filename);
		return -1;
	}

	while(fgets(line,1020,fp)){
		struct item_data *id=NULL;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,p=line;j<2 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(str[0] == NULL || str[1] == NULL)
			continue;

		nameid = atoi(str[0]);
		if(nameid < 0 || !(id = itemdb_exists(nameid)))
			continue;
		k = atoi(str[1]);
		if(k > 0) {
			id->flag.available = 1;
			id->view_id = k;
		} else {
			id->flag.available = 0;
		}
		ln++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename, ln);
	return 0;
}
