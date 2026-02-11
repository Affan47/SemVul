fileClose(AjPFile thys)
{
    int sleepcount = 0;
    int status = 0;
    int maxsleep = 60;
#ifndef WIN32
    pid_t retval;
#endif

    if(!thys)
        return;

#ifndef WIN32


    if (thys->Pid && thys->End)
    {
        while((retval=waitpid(thys->Pid,&status,WNOHANG))!= thys->Pid)
        {
            if(sleepcount > maxsleep)
                break;

            sleepcount++;
            sleep(1);


            if(retval == -1)
                if(errno != EINTR)
                    break;

            status = 0;
        }
    }
#else
    if(thys->Process && thys->End)
    {
        WaitForSingleObject(thys->Process,INFINITE);
        CloseHandle(thys->Process);
        CloseHandle(thys->Thread);
    }

#endif

    if(thys->Handle)
    {
        if(thys->fp)
        {
            if(thys->fp == stdout)
                fileUsedStdout = ajFalse;
            else if(thys->fp == stderr)
                fileUsedStderr = ajFalse;
            else if(thys->fp == stdin)
                fileUsedStdin = ajFalse;
            else
            {
                if(fclose(thys->fp))
                    ajFatal("File close problem in fileClose error:%d '%s'",
                            errno, strerror(errno));
            }
        }

        thys->Handle = 0;

        fileCloseCnt++;
        fileOpenCnt--;
    }
    else
        ajDebug("file already closed\n");

    ajStrDel(&thys->Name);
    ajStrDel(&thys->Printname);
    ajStrDel(&thys->Buff);
    ajListstrFreeData(&thys->List);
    AJFREE(thys->Workbuffer);
    AJFREE(thys->Readblock);

    return;
}
