fl_end_command( FL_PID_T pid )
{
    PIDList *cur,
            *last;
    int pstat;

    for ( last = 0, cur = pidlist;
          cur && cur->pid != pid;
          last = cur, cur = last->next )
         ;

    if ( ! cur )
        return -1;

    do
    {
        check_for_activity( cur );
        pid = waitpid( cur->pid, &pstat, 0 );
    } while ( pid == -1 && errno == EINTR );

    if ( last )
        last->next = cur->next;
    else
        pidlist = cur->next;

    fl_free( cur );

    return pid == -1 ? -1 : pstat;
}
