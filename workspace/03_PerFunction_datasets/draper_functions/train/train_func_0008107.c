proc_clone(VALUE self)
{
    VALUE procval = proc_dup(self);
    CLONESETUP(procval, self);
    return procval;
}
