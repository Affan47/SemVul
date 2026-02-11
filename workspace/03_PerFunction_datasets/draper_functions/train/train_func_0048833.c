update_segment(AFFILE *af,const char *segname,
		    const char *argstr,const char *segval)
{
    unsigned long arg = 0;

    if(strlen(argstr)>1) arg = atoi(argstr+1);

    if(!strcmp(segval,"=-")){
	get_segment_from_file(af,segname,arg,stdin);
	return;
    }
    if(!strncmp(segval,"=<",2)){
	FILE *f = fopen(segval+2,"rb");
	if(!f) err(1,"fopen(%s)",segval+2);
	get_segment_from_file(af,segname,arg,f);
	fclose(f);
	return;
    }
    segval++;
    int r = af_update_seg(af,segname,arg,(const u_char *)segval,strlen(segval));
    if(r) warn("af_update(%s,%s) ",af_filename(af),segname);
}
