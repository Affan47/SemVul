keyval(char *line, unsigned int len, char **key, char **val){
	char *ptr;
	ptr= line;


	while( (*ptr==' ' || *ptr=='\t') && ptr < (line+len))
		ptr++;


	if(ptr==(line+len) || *ptr=='#' || *ptr=='=' || *ptr=='\r' || *ptr=='\n')
		return 0;

	*key=ptr;


	while( (*ptr!=' ' && *ptr!='\t' && *ptr!='\r' && *ptr!='\n' && *ptr!='#' && *ptr!='=') && ptr < (line+len))
		ptr++;


	if(ptr==(line+len) || *ptr=='#' || *ptr=='\r' || *ptr=='\n')
		return -1;


	if(*ptr==' ' || *ptr=='\t'){

		*ptr=0;
		ptr++;

		while(ptr<(line+len) &&  (*ptr==' ' || *ptr=='\t'))
			ptr++;

		if(ptr==(line+len) || *ptr!='=')
			return -1;

		ptr++;
	}else{

		*ptr=0;
		ptr++;
	}


	while( (*ptr==' ' || *ptr=='\t') && ptr<(line+len))
		ptr++;


	*val=ptr;


	while( (*ptr!='#' && *ptr!='\r' && *ptr!='\n' && *ptr!='\t' && *ptr!='=' && *ptr!=' ') && ptr < (line+len))
		ptr++;


	if(ptr == *val)
		return(-1);

	*ptr=0;
	return(1);
}
