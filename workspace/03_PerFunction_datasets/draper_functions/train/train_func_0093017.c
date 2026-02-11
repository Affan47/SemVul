parms(void)
{
    char *p;
    int t;
    p=getenv("tmp_dir"); if(p!=NULL && *p!=0) tmpdir=p;
    p=getenv("texgif_tmpdir"); if(p!=NULL && *p!=0) tmpdir=p;
    p=getenv("texgif_fontdir"); if(p!=NULL && *p!=0) fontdir=p;
    p=getenv("texgif_outfile"); if(p!=NULL && *p!=0) outfile=p;
    p=getenv("texgif_texheader"); if(p!=NULL && *p!=0) headerfile=p;
    p=getenv("texgif_style"); if(p!=NULL && *p!=0) texstyle=p;
    p=getenv("texgif_density"); if(p!=NULL && *p!=0) {
	t=atoi(p); if(t>10 && t<1000) basedensity=t;
    }
    p=getenv("texgif_compressratio"); if(p!=NULL && *p!=0) {
	t=atoi(p); if(t>1 && t<=5) compressratio=t;
    }
    if(getcwd(cwd,sizeof(cwd))==NULL) cwd[0]=0;
}
