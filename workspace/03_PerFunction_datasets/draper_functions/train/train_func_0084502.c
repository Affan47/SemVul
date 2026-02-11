SITECHANbilge(sp)
    register SITE  *sp;
{
    int             fd, i;
    char            buff[SPOOLNAMEBUFF];
    char           *name;

    name = sp->SpoolName;
    fd = open(name, O_APPEND | O_CREAT | O_WRONLY, BATCHFILE_MODE);
    if (fd < 0 && errno == EISDIR) {
        FileGlue(buff, sp->SpoolName, '/', "togo");
        name = buff;
        fd = open(buff, O_APPEND | O_CREAT | O_WRONLY, BATCHFILE_MODE);
    }
    if (fd < 0) {
	int oerrno = errno ;
        syslog(L_ERROR, "%s cant open %s %m", sp->Name, name);
        IOError("site batch file",oerrno);
        sp->Channel = NULL;
        return FALSE;
    }
    while(sp->Channel->Out.Left > 0) {
        i = write(fd, (POINTER) &sp->Channel->Out.Data[sp->Channel->Out.Used],
            (SIZE_T) sp->Channel->Out.Left);
        if(i <= 0) {
            syslog(L_ERROR,"%s cant spool count %d",CHANname(sp->Channel),
                sp->Channel->Out.Left);
            close(fd);
            return FALSE;
        }
        sp->Channel->Out.Left -= i;
        sp->Channel->Out.Used += i;
    }
    close(fd);
    DISPOSE(sp->Channel->Out.Data);
    sp->Channel->Out.Data = NEW(char, SMBUF);
    sp->Channel->Out.Size = SMBUF;
    sp->Channel->Out.Left = 0;
    sp->Channel->Out.Used = 0;
    return TRUE;
}
