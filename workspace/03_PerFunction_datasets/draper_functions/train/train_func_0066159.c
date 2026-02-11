do_repeat(Proc *proc)
{
    prog_run(proc->prog, NULL, 0, "\bREPEAT", 0);
    if (proc->count > 0) --proc->count;
    return proc->count;
}
