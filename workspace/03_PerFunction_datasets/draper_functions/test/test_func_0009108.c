dbg_detach(proc_t *p)
{
	if (p->flags & DBGPROC_TRACED) {
#if defined(DBG_LINUX)
		ptrace(PTRACE_DETACH, p->pid, 0, 0);
#elif defined(DBG_SOLARIS)

		close(p->mem_fd);
		p->mem_fd = -1;
#elif defined(DBG_FREEBSD) || defined(DBG_NETBSD) || defined(DBG_OPENBSD)
		ptrace(PT_DETACH, p->pid, 0, 0);
#elif defined(DBG_HPUX)
		ttrace(TT_PROC_DETACH, pid, 0, 0, 0, 0);
#endif
		p->flags &= ~DBGPROC_TRACED;
		if (dbg_verbose)
			fprintf(stdout, "dbg: detached from process %u\n", p->pid);
	}
}
