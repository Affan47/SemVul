HyperLoadFile(hyper,fname)
HyperWidget hyper;
char   *fname;
{
    Widget widget = (Widget) hyper;
#if !defined(__GLIBC__) || __GLIBC__ < 2
    extern char *sys_errlist[];
#endif

    FILE *f = fopen(fname,"r");
    fprintf(stderr,"opening info file %s\n",fname);
    if(f)
    {
        set_text(hyper,get_from_file,(XtPointer)f);
        fclose(f);
    }
    else
    {
        char msg[1024];
        sprintf(msg,"%s: %s",fname,sys_errlist[errno]);
        XtWarning(msg);
    }

}
