extra_translate(
	struct afp_volume * volume, const char * path,
	char ** newpath_p)
{

	char * p;
	char * newpath;
	*newpath_p=NULL;
	if (~volume->extra_flags & VOLUME_EXTRA_FLAGS_SHOW_APPLEDOUBLE)
		return 0;

	if (strcmp(path,servericon_string)==0)
		return AFP_META_SERVER_ICON;

	if (strlen(path)<(strlen(appledouble)+1))
		return 0;

	if ((p=strrchr(path,'/'))==NULL)
		return 0;

	p+=1;

	if (strcmp(p,appledouble)==0) {


		newpath = malloc(strlen(path));
		memset(newpath,0,strlen(path));
		if (strlen(path)==strlen(appledouble)+1)
			newpath[0]='/';
		else
			memcpy(newpath,path,strlen(path)-(strlen(appledouble)+1));
		*newpath_p=newpath;

		return AFP_META_APPLEDOUBLE;
	}

	if ((p=strstr(path,appledouble))) {

		newpath = malloc(strlen(path));
		memset(newpath,0,strlen(path));
		memcpy(newpath,path,p-path);
		p+=strlen(appledouble);
		strcat(newpath,p+1);
		*newpath_p=newpath;


		if (strlen(newpath)>strlen(finderinfo_string)) {
			p=newpath+strlen(newpath)-strlen(finderinfo_string);
			if (strcmp(p,finderinfo_string)==0) {
				*p='\0';
				return AFP_META_FINDERINFO;
			}
		}

		if (strlen(newpath)>strlen(comment_string)) {
			p=newpath+strlen(newpath)-strlen(comment_string);
			if (strcmp(p,comment_string)==0) {
				*p='\0';
				return AFP_META_COMMENT;
			}
		}

		return AFP_META_RESOURCE;
	}

	return 0;
}
