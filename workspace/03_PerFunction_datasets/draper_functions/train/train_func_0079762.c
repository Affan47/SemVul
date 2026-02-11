onedir(char *dirname)
{
    char buf[MAX_LINELEN+1], buf2[MAX_LINELEN+1];
    DIR *dir;
    struct dirent *ff;
    char *t1, *t2;

    for(t1=find_word_start(types); *t1; t1=find_word_start(t2)) {
	t2=find_word_end(t1); if(*t2) *t2++=0;
	snprintf(buf,sizeof(buf),"%s/%s/%s",dirbase,dirname,t1);
	dir=opendir(buf); if(dir==NULL) return;
	while((ff=readdir(dir))!=NULL) {
	    if(!isalnum(ff->d_name[0]) ||
	       strcmp(ff->d_name,"supervisor")==0) continue;
	    snprintf(buf2,sizeof(buf2),"%s/%s",buf,ff->d_name);
	    onefile(buf2);
	}
	closedir(dir);
    }
}
