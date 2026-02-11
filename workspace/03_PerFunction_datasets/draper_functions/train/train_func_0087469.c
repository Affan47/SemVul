_dxf_ExLogOpen ()
{
    lfd = creat ("dx.log", 0666);
    if (lfd >= 0)
	lfp = fdopen (lfd, "w");

    if(lfd < 0 || lfp == NULL)
        return(errno);
    else return(0);
}
