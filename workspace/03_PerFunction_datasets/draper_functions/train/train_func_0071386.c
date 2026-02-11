proc_mark(void *ptr)
{
    rb_proc_t *proc;
    RUBY_MARK_ENTER("proc");
    if (ptr) {
	proc = ptr;
	RUBY_MARK_UNLESS_NULL(proc->envval);
	RUBY_MARK_UNLESS_NULL(proc->blockprocval);
	RUBY_MARK_UNLESS_NULL(proc->block.proc);
	RUBY_MARK_UNLESS_NULL(proc->block.self);
	if (proc->block.iseq && RUBY_VM_IFUNC_P(proc->block.iseq)) {
	    RUBY_MARK_UNLESS_NULL((VALUE)(proc->block.iseq));
	}
    }
    RUBY_MARK_LEAVE("proc");
}
