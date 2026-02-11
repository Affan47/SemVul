resume_from_tcp (struct tcb *tcp)
{
	int error = 0;
	int resumed = 0;


	if (tcp->parent &&
	    (tcp->parent->flags & TCB_SUSPENDED) &&
	    (tcp->parent->waitpid <= 0 || tcp->parent->waitpid == tcp->pid)) {
		error = resume(tcp->parent);
		++resumed;
	}
#ifdef TCB_CLONE_THREAD
	if (tcp->parent && tcp->parent->nclone_waiting > 0) {

		unsigned int i;


		for (i = 0; i < tcbtabsize; i++) {
			struct tcb *t = tcbtab[i];
			if (t->parent == tcp->parent && t != tcp
			    && ((t->flags & (TCB_CLONE_THREAD|TCB_SUSPENDED))
				== (TCB_CLONE_THREAD|TCB_SUSPENDED))
			    && t->waitpid == tcp->pid) {
				error |= resume (t);
				++resumed;
			}
		}
		if (resumed == 0)


			for (i = 0; i < tcbtabsize; i++) {
				struct tcb *t = tcbtab[i];
				if (t->parent == tcp->parent && t != tcp
				    && ((t->flags
					 & (TCB_CLONE_THREAD|TCB_SUSPENDED))
					== (TCB_CLONE_THREAD|TCB_SUSPENDED))
				    && t->waitpid <= 0
					) {
					error |= resume (t);
					break;
				}
			}
	}
#endif

	return error;
}
