MyGetString(char *str, int strlen)
{
	if (fgets(str, strlen, stdin)!=NULL){
		char *eot;
		char *newline = strchr(str,'\n');
		if (newline!=NULL)
			*newline = '\0';
		else
			readRestOfLine();
		eot = strchr(str, 4);
		if (eot!=NULL)
			return NULL;
		return Trim(str);
	}
	return NULL;
}
