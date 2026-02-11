sp_basename(char *path)
{
		char *end = path + strlen(path);
		while(end!=path && !isslash2(*end)) end--;
		if(isslash2(*end))
			memmove(path,end+1,strlen(end+1)+1);
		else
			if(end!=path) memmove(path,end,strlen(end)+1);
		return path;
}
