procdef_new (int typeid, int id)
{
    PROCDEF * proc = (PROCDEF *) malloc (sizeof(PROCDEF)) ;
    int n ;

    if (!proc)
    {
        fprintf (stderr, _("procdef_new: out of memory\n")) ;
        exit (1) ;
    }

    proc->pridata = segment_new() ;
    proc->privars = varspace_new() ;


    proc->pubdata = segment_new() ;
    proc->pubvars = varspace_new() ;


    proc->params    = -1 ;
    proc->defined   = 0 ;
    proc->declared  = 0 ;
    proc->type      = TYPE_DWORD ;
    proc->flags     = 0 ;

    proc->sentence_count = 0 ;
    proc->sentences      = 0 ;

    if (typeid >= procs_allocated)
    {
        procs_allocated = typeid + 15 ;
        procs = (PROCDEF **) realloc (procs, sizeof(PROCDEF **) * procs_allocated) ;
        if (!procs)
        {
            fprintf (stderr, _("procdef_new: out of memory\n")) ;
            exit (1) ;
        }
    }
    proc->typeid     = typeid ;
    proc->identifier = id ;
    procs[typeid]    = proc ;

    for (n = 0 ; n < MAX_PARAMS ; n++)
        proc->paramtype[n] = TYPE_UNDEFINED ;

    proc->exitcode  = 0 ;

    codeblock_init (&proc->code) ;
    procdef_count++ ;
    return proc ;
}
