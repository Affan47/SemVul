rb_proc_lambda_p(VALUE procval)
{
    rb_proc_t *proc;
    GetProcPtr(procval, proc);

    return proc->is_lambda ? Qtrue : Qfalse;
}
